//
//  player.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/23.
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include <string>
#include <vector>

class Player{
public:
    Player(int max_hp, int hp , std::string &charName, int position, int amount = 0){
        Max_hp_ = hp;
        hp_ = hp;
        charName_ = charName;
        position_ = position;
        holding_card_amount_ = amount;
    }
    
    int get_Max_hp();
    int get_hp();
    const std::string& get_charName() const;
    int get_holding_card_amount();
    const std::vector<int>& get_holding() const;
    int get_equipment();
    int get_position();
    bool isJail();
    
    void set_Max_hp(int hp);
    void set_hp(int hp);
    void set_charName(std::string &Name);
    void set_holding_card_amount(int amount);
    bool use_card(int card);
    void add_card(int card);
    void set_position(int pos);
    void set_Jail(bool isJail);
    
private:
    int Max_hp_;
    int hp_;
    std::string charName_;
    int holding_card_amount_;
    std::vector<int> holding_;
    int equipment_;
    int position_;
    bool isJail_;
};

#endif /* player_hpp */
