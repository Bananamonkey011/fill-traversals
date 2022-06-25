
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

#include <iostream>

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  PNG png = PNG();
  png.readFromFile("alma.png");
  // std::cout<<__LINE__<<std::endl;
  FloodFilledImage img = FloodFilledImage(png);
  // std::cout<<__LINE__<<std::endl;

  MyColorPicker one = MyColorPicker();
  // std::cout<<__LINE__<<std::endl;
  SolidColorPicker two = SolidColorPicker(HSLAPixel(11, .81, .53));
  // std::cout<<__LINE__<<std::endl;

  BFS travOne = BFS(png, Point(250,3), .3);
  // std::cout<<__LINE__<<std::endl;
  DFS travTwo = DFS(png, Point(250,150), .35);


  // std::cout<<__LINE__<<std::endl;
  img.addFloodFill(travOne,one);
  img.addFloodFill(travTwo,two);
  // std::cout<<__LINE__<<std::endl;
  std::cout<<png.width()<<" "<<png.height()<<std::endl;

  Animation animation = img.animate(1800);
  // std::cout<<__LINE__<<std::endl;
  
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  


  return 0;
}
