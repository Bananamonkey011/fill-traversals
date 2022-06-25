#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel &p1, const HSLAPixel &p2)
{
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180)
  {
    h = 360 - h;
  }
  h /= 360;

  return sqrt((h * h) + (s * s) + (l * l));
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator()
{
  /** @todo [Part 1] */
  isEnd_ = true;
}

ImageTraversal::Iterator::Iterator(ImageTraversal *traversal, Point start)
{
  /** @todo [Part 1] */
  traversal_ = traversal;
  start_ = start;
  cur_ = start;
  isEnd_ = false;

  addNeighbors();
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator &ImageTraversal::Iterator::operator++()
{
  /** @todo [Part 1] */
  Point pt = cur_;
  while (!(traversal_->empty()) && traversal_->isVisited(pt.x, pt.y))
  {
    pt = traversal_->pop();
  }
  if (!traversal_->empty())
  {
    cur_ = pt;
    traversal_->visit(cur_.x, cur_.y);
    addNeighbors();
  } else {
    isEnd_ = true;
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*()
{
  /** @todo [Part 1] */
  return cur_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other)
{
  /** @todo [Part 1] */

  return !(isEnd() && other.isEnd());
}
bool ImageTraversal::Iterator::isEnd() const {
  return isEnd_;
}
void ImageTraversal::Iterator::addNeighbors()
{
  const HSLAPixel current = traversal_->getPNG()->getPixel(start_.x, start_.y);

  // std::cout << cur_ << " ";

  if (cur_.x + 1 < traversal_->getPNG()->width() && calculateDelta(current, traversal_->getPNG()->getPixel(cur_.x + 1, cur_.y)) <= traversal_->tolerance())
  {
    // std::cout << Point(cur_.x + 1, cur_.y) << " ";
    traversal_->add(Point(cur_.x + 1, cur_.y));
  }
  if (cur_.y + 1 < traversal_->getPNG()->height() && calculateDelta(current, traversal_->getPNG()->getPixel(cur_.x, cur_.y + 1)) <= traversal_->tolerance())
  {
    // std::cout << Point(cur_.x, cur_.y + 1) << " ";
    traversal_->add(Point(cur_.x, cur_.y + 1));
  }
  if (cur_.x > 0 && calculateDelta(current, traversal_->getPNG()->getPixel(cur_.x - 1, cur_.y)) <= traversal_->tolerance())
  {
    // std::cout << Point(cur_.x - 1, cur_.y) << " ";
    traversal_->add(Point(cur_.x - 1, cur_.y));
  }
  if (cur_.y > 0 && calculateDelta(current, traversal_->getPNG()->getPixel(cur_.x, cur_.y - 1)) <= traversal_->tolerance())
  {
    // std::cout << Point(cur_.x, cur_.y - 1) << " ";
    traversal_->add(Point(cur_.x, cur_.y - 1));
  }
  // std::cout << "\n";
}
