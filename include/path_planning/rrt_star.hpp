/**
 * @file rrt_star.hpp
 * @author vss2sn
 * @brief Contains the RRTStar class
 */

#ifndef RRT_STAR_H
#define RRT_STAR_H

#include <limits>
#include <unordered_map>
#include <tuple>
#include <vector>


#include "path_planning/planner.hpp"

#include "utils/utils.hpp"

/**
 * @brief Class for RRT Star objects
 */
class RRTStar : public Planner {
public:

  RRTStar(std::vector<std::vector<int>> grid) : Planner (std::move(grid)) {}

 /**
  * @brief Main algorithm of A*
  * @param grid Main grid
  * @param start_in start node
  * @param goal_in goal node
  * @return vector of path
  */
  std::tuple<bool, std::vector<Node>> Plan(const Node& start_in, const Node& goal_in) override;

private:
  /**
   * @brief Find the nearest Node that has been seen by the algorithm. This does
   * not consider cost to reach the node.
   * @param new_node Node to which the nearest node must be found
   * @return nearest node
   */
   std::tuple<bool, Node> FindNearestPoint(Node& new_node);

  /**
   * @brief Check if there is any obstacle between the 2 nodes. As this planner
   * is for grid maps, the obstacles are square.
   * @param n_1 Node 1
   * @param n_2 Node 2
   * @return bool value of whether obstacle exists between nodes
   */
  bool IsAnyObstacleInPath(const Node& n_1, const Node& n_2) const;

  /**
   * @brief Generates a random node
   * @return Generated node
   */
  Node GenerateRandomNode() const;

  /**
   * @brief Rewire the tree
   * @param new_node Node to which other nodes will be connected if their cost
   * decreases
   * @return void
   */
  void Rewire(const Node& new_node);

  /**
   * @brief Check if goal is reachable from current node
   * @param new_node Current node
   * @return bool value of whether goal is reachable from current node
   */
  bool CheckGoalVisible(const Node& new_node);

  /**
   * @brief Create the obstacle list from the input grid
   * @return void
   */
  void CreateObstacleList();

  std::vector<Node> CreatePath();

 private:
  Node start, goal;
  std::unordered_set<Node, NodeIdAsHash, compare_coordinates> point_list_;  // TODO: set up in cstor
  std::unordered_map<Node, std::vector<Node>>  near_nodes_;
  std::vector<Node> obstacle_list_;
  double threshold_ = 1.5; // TODO: set up in cstor
  int max_iter_x_factor_ = 500; // TODO: set up in cstor
};

#endif  // RRT_STAR_H
