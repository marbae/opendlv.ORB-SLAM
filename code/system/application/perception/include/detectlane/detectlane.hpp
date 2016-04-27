/**
 * Copyright (C) 2015 Chalmers REVERE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 */

#ifndef DETECTLANE_DETECTLANE_HPP_
#define DETECTLANE_DETECTLANE_HPP_

#include <memory>
#include <Eigen/Dense>
#include "opendavinci/odcore/base/module/DataTriggeredConferenceClientModule.h"
#include "opendavinci/odcore/data/Container.h"

namespace opendlv {
namespace perception {
namespace detectlane {

/**
 * This class provides...
 */
class DetectLane
: public odcore::base::module::DataTriggeredConferenceClientModule {
 public:
  DetectLane(int32_t const &, char **);
  DetectLane(DetectLane const &) = delete;
  DetectLane &operator=(DetectLane const &) = delete;
  virtual ~DetectLane();
  virtual void nextContainer(odcore::data::Container &);

 private:
  int m_width;
  int m_height;
  int m_maxRow;
  int m_minRow;
  int m_p1;
  int m_p2;
  int m_midRegion;
  int m_threshold;
  double m_laneOffset;
  double m_d1;
  double m_d2;
  double m_theta;

  bool m_initialized;

  // Matrix holding region lines
  Eigen::MatrixXd m_regions;
  Eigen::MatrixXd m_leftCameraRegions;
  Eigen::MatrixXd m_rightCameraRegions;
  
  // Matrix holding the lines col = row * k + m for the region lines
  Eigen::MatrixXd m_lines;
  
  // Number of scan lines / points
  int m_nPoints;
  // Number of search regions
  long m_nRegions;

  // Matrix holding the mean column for each region on each row
  Eigen::MatrixXd m_recoveredPoints;

  // Holds the K and M parameters for each region
  Eigen::MatrixXd m_K;
  Eigen::MatrixXd m_M;
  Eigen::MatrixXd m_k;
  Eigen::MatrixXd m_m;
  // Counts the number of points per each region
  Eigen::VectorXd m_pointsPerRegion;
  
  // Holds the index that decides the left and right road track
  Eigen::MatrixXd m_regionIndex;
  
  // Holds the location of found lanes
  Eigen::VectorXd m_laneLocation2;
  

  void setUp();
  void tearDown();
};

} // detectlane
} // perception
} // opendlv

#endif
