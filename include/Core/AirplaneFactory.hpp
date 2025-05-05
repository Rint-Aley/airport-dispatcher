#pragma once

#include <memory>
#include <functional>
#include <string>
#include <unordered_map>

#include "IAirplane.hpp"

namespace Core {

    class AirplaneFactory {
    public:
        /// функция для создания нового экземпляра самолета
        using Creator = std::function<std::unique_ptr<IAirplane>(int, FlightRole)>;

        /// запись в хеш таблицу
        static void register_type(const std::string& type, const Creator& creator);

        /// создает экземпляр unique_ptr (пока он живет, живут все raw указатели)
        /// @throws std::runtime_error если тип модуля не найден
        static std::unique_ptr<IAirplane> create(const std::string& name, int id, FlightRole role);

    private:
        /// используем хеш таблицу для поиска по string нужного типа самолета (для o(1))
        static std::unordered_map<std::string, Creator>& get_registry();
    };

}
