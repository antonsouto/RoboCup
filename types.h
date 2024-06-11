#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <ostream>
#include <array>

using namespace std;

enum FIELD
{
  LEFT,
  RIGHT
};

struct MatchInit
{
  FIELD field;
  int number;
};

struct BallData
{
  double distance;
  double direction;
  double distance_change;
  double direction_change;
};

enum REFEREE_MESSAGE
{
  DROP_BALL,
  PLAY_ON,
  UNKNOWN
};

struct MatchData
{
  int time;
};

struct SeeData
{
  BallData ball;
};

struct Player
{
  MatchInit config;
  MatchData match;
  SeeData see;
  REFEREE_MESSAGE referee_message;
};

ostream &operator<<(ostream &os, const MatchInit &response);

ostream &operator<<(ostream &os, const SeeData &see);
ostream &operator<<(ostream &os, const BallData &ball);
ostream &operator<<(ostream &os, const MatchData &match);

ostream &operator<<(ostream &os, const Player &player);

#endif // TYPES_H
