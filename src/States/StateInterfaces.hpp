//
// Created by Vince on 2024. 04. 30..
//

#ifndef SFML_NHZ_STATEINTERFACES_HPP
#define SFML_NHZ_STATEINTERFACES_HPP

#include "State.h"

//Button interface
class iButton: virtual public State{
protected:
    std::map<std::string, Button*> buttons;
public:
    virtual void initButtons() = 0; //initializes buttons
    virtual void handleButtons() = 0; //handles buttons
    void updateButtons(){   //updates buttons
        for(auto &it : this->buttons)
            it.second->update(this->mousePosView);
        handleButtons();
    }
    void renderButtons(sf::RenderTarget *target) {  //renders buttons
        for(auto &it : this->buttons)
            it.second->render(target);
    }
    void deleteButtons(){   //deletes allocated buttons
        auto it = this->buttons.begin();
        for (it = this->buttons.begin(); it != this->buttons.end(); ++it){
            it->second;
        }
    }
};

//Slider interface
class iSlider: virtual public State{
protected:
    std::map<std::string, Slider*> sliders;
public:
    virtual void initSliders() = 0; //initializes slider
    virtual void handleSliders() = 0; //handles sliders
    void updateSliders() {  //updates sliders
        for(auto &it : this->sliders)
            it.second->update(this->mousePosView);
        handleSliders();
    }
    void renderSliders(sf::RenderTarget *target) {  //renders sliders
        for(auto &it : this->sliders)
            it.second->render(target);
    }
    void deleteSliders(){   //deletes allocated sliders
        auto it = this->sliders.begin();
        for (it = this->sliders.begin(); it != this->sliders.end(); ++it){
            it->second;
        }
    }
};


//Stores the games parameters
class Difficulty{
public:
    int columns, rows, bombs;
    Difficulty(int columns, int rows, int bombs):
    columns(columns), rows(rows), bombs(bombs){}
};


#endif //SFML_NHZ_STATEINTERFACES_HPP
