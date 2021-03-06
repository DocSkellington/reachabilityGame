/*
 * ReachabilityGame - a program to compute the best Nash equilibrium in reachability games
 * Copyright (C) 2018 Gaëtan Staquet and Aline Goeminne
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "ReachabilityGame.hpp"

#include <iostream>
#include <queue>

using namespace types;
using namespace exploration;

ReachabilityGame::ReachabilityGame(Graph graph, Vertex::Ptr init, const std::vector<Player>& players) :
    Game(graph, init),
    m_players(players),
    m_maxWeightsPath(players.size())
    {
    for (std::size_t i = 0 ; i < players.size() ; i++) {
        // Le poids maximal pour un chemin est (|Pi| + 1) * |V| * max(|w_i|)
        m_maxWeightsPath[i] = Long(getMaxLength()) * getGraph().getMaxWeights()[i];
    }
}

const std::vector<Player> &ReachabilityGame::getPlayers() const {
    return m_players;
}

std::size_t ReachabilityGame::getMaxLength() const {
    return (m_players.size() + 1) * getGraph().size();
}

void ReachabilityGame::printDOT() const {
    std::cout << "digraph G {\n";
    for (auto itr = m_graph.cbegin() ; itr != m_graph.cend() ; ++itr) {
        const Vertex::Ptr vertex = *itr;

        std::cout << *vertex << "[label=\"" << *vertex << "\", shape=";

        if (vertex->getPlayer() == 0) {
            std::cout << "circle";
        }
        else {
            std::cout << "square";
        }

        if (vertex->isTargetFor(0)) {
            std::cout << ", color=red";
        }
        if (vertex->isTargetFor(1)) {
            std::cout << ", style=dotted";
        }

        std::cout << "];\n";
    }

    for (auto itr = m_graph.cbegin() ; itr != m_graph.cend() ; ++itr) {
        const Vertex::Ptr v = *itr;
        for (auto edge : *v) {
            const Vertex::Ptr u = edge.second.first.lock();
            const std::vector<Long> &weights = edge.second.second;

            std::cout << *v << " -> " << *u << "[label=\"(";
            for (std::size_t i = 0 ; i < weights.size() ; i++) {
                if (i != 0) {
                    std::cout << ", ";
                }
                std::cout << weights[i];
            }
            std::cout << ")\"]\n";
        }
    }

    std::cout << "}\n";
}

Long ReachabilityGame::AStartPositive(const Node::Ptr& node, const CostsMap &costsMap) {
    const std::vector<Long> &epsilon = node->state.epsilon;
    // g(n) = Coût vers les cibles déjà atteintes + coûts partiels (joueurs qui n'ont pas encore atteints une cible)
    Long g_n = node->state.RP;
    for (unsigned int notReached : node->state.notVisitedPlayers) {
        g_n += epsilon[notReached];
    }

    Long h_n = 0;
    for (unsigned int notReached : node->state.notVisitedPlayers) {
        Long shortest = Long::infinity;
        for (const Vertex::Ptr goal : m_players[notReached].getGoals()) {
            auto itr = costsMap.find(goal);
            const CostsForATarget& target = itr->second;
            shortest = std::min(shortest, target[node->path.getLast()->getID()]);
        }
        h_n += std::min(shortest, m_maxWeightsPath[notReached] - epsilon[notReached]);
    }

    return g_n + h_n;
}

std::size_t ReachabilityGame::percentageOfReachableVertices() const {
    std::size_t nReachable = 0;
    std::queue<Vertex::Ptr> queue;
    std::unordered_set<Vertex::Ptr> explored;

    queue.push(m_init);
    explored.insert(m_init);

    while (!queue.empty()) {
        const Vertex::Ptr v = queue.front();
        queue.pop();
        nReachable++;

        for (auto itr : *v) {
            const Vertex::Ptr u = itr.second.first.lock();

            // Si on n'a pas encore exploré ce noeud
            if (explored.find(u) == explored.end()) {
                queue.push(u);
                explored.insert(u);
            }
        }
    }

    return nReachable * 100./getGraph().size();
}

std::ostream& operator<<(std::ostream &os, const ReachabilityGame &game) {
    os << "size: " << game.getGraph().size() << ", nPlayers: " << game.getPlayers().size() << '\n';
    os << "init: " << *game.getInit() << '\n';
    for (auto v : game.getGraph().getVertices()) {
        os << *v << " belongs to player " << v->getPlayer() << " and is a target for ";
        for (unsigned int p : v->getTargetPlayers()) {
            os << p << ", ";
        }

        os << "\nedges to: {\n";
        for (auto edge : *v) {
            os << '\t' << *edge.second.first.lock() << " (";
            for (Long p : edge.second.second) {
                os << p << ", ";
            }
            os << ")\n";
        }
        os << "}\n";
    }

    return os;
}