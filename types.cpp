#include "types.h"
#include <ostream>

using namespace std;

ostream &operator<<(ostream &os, const MatchInit &response)
{
  os << "\nMatchInitResponse:\n-------------------\n";
  os << "Field:\t" << (response.field == FIELD::LEFT ? "LEFT" : "RIGHT");
  os << "\nNumber:\t" << response.number << "\n-------------------\n";
  return os;
}

ostream &operator<<(ostream &os, const SeeData &see)
{
  os << "\nSeeData:\n-------------------\n";
  os << "Ball:\t" << see.ball;
  os << "\n-------------------\n";
  return os;
}
ostream &operator<<(ostream &os, const BallData &ball)
{
  os << "\nBallData:\n-------------------\n";
  os << "Distance:\t" << ball.distance;
  os << "\nDirection:\t" << ball.direction;
  os << "\nDistance Change:\t" << ball.distance_change;
  os << "\nDirection Change:\t" << ball.direction_change;

  os << "\n-------------------\n";
  return os;
}
ostream &operator<<(ostream &os, const MatchData &match)
{
  os << "\nMatchData:\n-------------------\n";
  os << "Time:\t" << match.time;
  os << "\n-------------------\n";
  return os;
}

ostream &operator<<(ostream &os, const Player &player)
{
  os << "Player:\n=====================================================\n";
  os << "Config: " << player.config;
  os << "Match: " << player.match;
  os << "See: " << player.see;
  os << "Referee Message: " << player.referee_message;
  return os;
}
