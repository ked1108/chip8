#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cstdint>

const unsigned int WIDTH = 64;
const unsigned int HEIGHT = 32;
const unsigned int SCALE = 15;


int main(){
  sf::Window window(sf::VideoMode(WIDTH*SCALE, HEIGHT*SCALE), "Chip8");
  while(window.isOpen()){
    sf::Event event;
    while(window.pollEvent(event)){
      if(event.type == sf::Event::Closed){
        window.close();
      }
    }
  }
}
