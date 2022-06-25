#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <iostream>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 *
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG &png, const Point &start, double tolerance) : png_(png), start_(start), tolerance_(tolerance)
{
  /** @todo [Part 1] */
  for (unsigned x = 0; x < png.width(); x++)
  {
    std::vector<bool> temp;
    for (unsigned y = 0; y < png.height(); y++)
    {
      temp.push_back(false);
    }
    visited_.push_back(temp);
    temp.clear();
  }
  toVisit_.push(start_);
  visit(start.x, start.y);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin()
{
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this, start_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end()
{
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point &point)
{
  /** @todo [Part 1] */
  toVisit_.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop()
{
  /** @todo [Part 1] */
  Point out = toVisit_.top();
  toVisit_.pop();
  return out;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const
{
  /** @todo [Part 1] */
  return toVisit_.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const
{
  /** @todo [Part 1] */
  return toVisit_.empty();
}

bool DFS::isVisited(unsigned int x, unsigned int y)
{
  return visited_[x][y];
}
void DFS::visit(unsigned int x, unsigned int y)
{
  visited_[x][y] = true;
}
PNG * DFS::getPNG()
{
  return &png_;
}
double DFS::tolerance()
{
  return tolerance_;
}
