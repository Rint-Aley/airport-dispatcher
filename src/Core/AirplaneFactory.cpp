#include <Core/AirplaneFactory.hpp>

#include <Core/Planes/Biplane.hpp>
#include <Core/Planes/BusinessJet.hpp>
#include <Core/Planes/MilitaryDrone.hpp>
#include <Core/Planes/WideAirliner.hpp>

using namespace Core;

namespace {
    [[maybe_unused]] const bool registered = []{
        using namespace Core;
        AirplaneFactory::register_type("Biplane", [](int id, FlightRole r) {
            return std::make_unique<Planes::Biplane>(id, r);
        });
        AirplaneFactory::register_type("BusinessJet", [](int id, FlightRole r) {
            return std::make_unique<Planes::BusinessJet>(id, r);
        });
        AirplaneFactory::register_type("MilitaryDrone", [](int id, FlightRole r) {
            return std::make_unique<Planes::MilitaryDrone>(id, r);
        });
        AirplaneFactory::register_type("WideAirliner", [](int id, FlightRole r) {
            return std::make_unique<Planes::WideAirliner>(id, r);
        });
        return true;
    }();
}

void AirplaneFactory::register_type(const std::string& type, const Creator& creator) {
    get_registry()[type] = creator;
}
std::unique_ptr<IAirplane> AirplaneFactory::create(const std::string& name, const int id, const FlightRole role) {
    const auto it = get_registry().find(name);
    if (it == get_registry().end())
        throw std::runtime_error("Unknown airplane type: " + name);
    return it->second(id, role);
}

std::unordered_map<std::string, AirplaneFactory::Creator>& AirplaneFactory::get_registry() {
    static std::unordered_map<std::string, Creator> registry;
    return registry;
}
