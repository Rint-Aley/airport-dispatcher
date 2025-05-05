#pragma once

#include <vector>
#include <nlohmann/json.hpp>

namespace Core {

    /// пока так
    struct TaxiwayManager {
        struct Node { int id; float x,y; };
        struct Edge { int u,v; float cost; };

        void add_node(const int id, const float x, const float y) { m_nodes.push_back({id,x,y}); }
        void add_edge(const int u, const int v, const float cost) { m_edges.push_back({u,v,cost}); }

        [[nodiscard]] const std::vector<Node>& get_nodes() const { return m_nodes; }
        [[nodiscard]] const std::vector<Edge>& get_edges() const { return m_edges; }

        static TaxiwayManager from_json(const nlohmann::json& j) {
            TaxiwayManager tm;
            for (auto& n : j.at("nodes")) {
                tm.add_node(n.at("id").get<int>(),
                           n.at("x").get<float>(),
                           n.at("y").get<float>());
            }
            for (auto& e : j.at("edges")) {
                tm.add_edge(e.at("u").get<int>(),
                           e.at("v").get<int>(),
                           e.at("cost").get<float>());
            }
            return tm;
        }

    private:
        std::vector<Node> m_nodes;
        std::vector<Edge> m_edges;
    };

}
