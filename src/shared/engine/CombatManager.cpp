// #include "CombatManager.h"
// #include "../../client/client.h"
// #include <iostream>
// #include <limits>

// namespace engine{

// //CombatManager::CombatManager(){
// //}


// state::Player* CombatManager::chooseOpponent(std::vector <state::Player*>& opponentsList, std::string name){ // à mettre dans client
    
//     //
//     if (opponentsList.empty()) {
//         std::cout << "You have no opponent, enjoy. " << name << "." << std::endl;
//         return nullptr;
//     }
//     std::cout << "Choose an opponent in your opponentsList : " << std::endl;

//     //
//     for (int i = 0; i < opponentsList.size(); ++i) {
//         state::Player* opponent = opponentsList[i];
//         std::cout << i + 1 << ". " << opponent->getName() << " (Position: " << opponent->getPosition() << ")" << std::endl;
//     }

//     //
//     int choice = 0;
//     while (true) {
//         std::cout << "Entrez le numéro de l'adversaire que vous voulez choisir : ";
//         std::cin >> choice;
//         if (std::cin.fail() || choice < 1 || choice > static_cast<int>(opponentsList.size())) {
//             std::cin.clear();
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//             std::cout << "Entrée invalide. Veuillez entrer un numéro valide." << std::endl;
//         } else {
//             break;
//         }
//     }
//     return opponentsList[choice - 1];
// }

// void CombatManager::duel(state::Player *playerAttack, state::Player *playerDefense){
//     //client::InputHandler inputHandler;
//     //inputHandler.chooseCanonNb()
// }
// }