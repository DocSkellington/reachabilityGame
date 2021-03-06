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

#pragma once

#include "ReachabilityGame.hpp"

namespace generators {
    /**
     * \brief Génère aléatoirement un jeu d'atteignabilité sur graphe fortement connexe.
     *
     * Le noeud initial est toujours v0.
     * 
     * Les poids des arcs sont toujours 1.
     * 
     * Pour chaque joueur, la probabilité qu'un sommet lui appartienne est 1/nPlayers.
     * 
     * Pour chaque joueur, la probabilité qu'un sommet soit une cible pour lui est 0.1.
     * 
     * Il n'y a pas de limites sur le nombre de cibles par joueur.
     * 
     * S'il arrive qu'un joueur n'a pas de cible, le paramètre sharedTargets est ignoré pour ce joueur.
     * 
     * \param size Le nombre de sommets
     * \param lowOutgoing Le nombre minimal d'arcs sortants par sommet
     * \param upOutgoing Le nombre maximal d'arcs sortants par sommet
     * \param nPlayers Le nombre de joueurs
     * \param sharedTargets Est-ce que plusieurs joueurs peuvent partager la même cible ?
     */
    ReachabilityGame randomStronglyConnectedGenerator(std::size_t size, std::size_t lowOutgoing, std::size_t upOutgoing, std::size_t nPlayers, bool sharedTargets);
    /**
     * \brief Génère aléatoirement un jeu d'atteignabilité sur graphe fortement connexe.
     * 
     * La précision sur les contraintes sur les paramètres est 1E-15.
     * 
     * Le noeud initial est toujours v0.
     * 
     * Les poids peuvent être négatifs.
     * 
     * S'il arrive qu'un joueur n'a pas de cible, le paramètre sharedTargets est ignoré pour ce joueur.
     * 
     * \param size Le nombre de sommets
     * \param lowOutgoing Le nombre minimal d'arcs sortants par sommet
     * \param upOutgoing Le nombre maximal d'arcs sortants par sommet
     * \param minWeight Le poids minimal
     * \param maxWeight Le poids maximal
     * \param multipleWeights Est-ce que les joueurs voient des poids différents sur un arc ?
     * \param nPlayers Le nombre de joueurs
     * \param sharedTargets Est-ce que plusieurs joueurs peuvent partager la même cible ?
     * \param probaPlayers Un tableau qui indique pour chaque joueur la probabilité qu'un sommet lui appartienne
     * \param probaTargets Un tableau qui indique pour chaque joueur la probabilité qu'un sommet soit une cible pour lui
     * \param maximumTargets Un tableau qui indique pour chaque joueur le nombre maximal de cibles qu'il peut avoir
     */
    ReachabilityGame randomStronglyConnectedGenerator(std::size_t size, std::size_t lowOutgoing, std::size_t upOutgoing, long minWeight, long maxWeight, bool multipleWeights, std::size_t nPlayers, bool sharedTargets, const std::vector<double>& probaPlayers, const std::vector<double>& probaTargets, const std::vector<types::Long>& maximumTargets);
}