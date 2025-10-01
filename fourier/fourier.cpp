#include"fourier.hpp"


bool Fourier::load_image(std::string filename){
    return (!texture.loadFromFile("data/capture.jpg")); 
};


