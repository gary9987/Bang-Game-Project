//
//  Card.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/23.
//

#ifndef Card_hpp
#define Card_hpp

#include <string>
enum class Suits{
    spades,//黑桃
    hearts,//紅心
    diamonds,//方塊
    clubs//梅花
};

class Card{
public:
    Card(int id, std::string &cardName, Suits suit, int number){
        card_id_ = id;
        cardName_ = cardName;
        suit_ = suit;
        number_ = number;
    }
    int get_id();
    const std::string& get_cardName() const;
    Suits get_suit();
    int get_number();
    const std::string& get_Description() const;
    
    void set_id(int id);
    void set_Name(std::string &name);
    void set_suit(Suits suit);
    void set_number(int number);
    void set_Description(std::string description);
    
private:
    int card_id_;
    std::string cardName_;
    std::string cardDescription_;
    Suits suit_;
    int number_;
};

#endif /* Card_hpp */