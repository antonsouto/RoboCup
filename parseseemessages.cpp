#include "parsehearmessages.h"
#include "parsehearmessages.h"
#include "stringutils.h"
#include <iostream>

namespace Parser
{
  /**
   * Player the hear message from the server
   * @param message hear message from the server
   * "hear 200 referee play_on"
   * "hear 339 referee play_on"
   * "hear time who message"
   * @return Player
   */
  Player &parseHearMessage(const std::string &message, Player &player)
  {
    if (!message.starts_with("hear"))
    {
      throw new std::runtime_error("Invalid hear message");
    }

    if (message.find("referee") != std::string::npos)
    {
      player.referee_message = Hear::parseReferee(message, player.referee_message);
    }
    else
    {
      cout << "Message not recognized: " << message << endl;
    }

    return player;
  }

  namespace Hear

  {

    /**
     * Player the referee message from the hear message
     * @param message hear message from the server
     * @return REFEREE_MESSAGE
     * @example PlayerRefereeMessage("hear 200 referee play_on") -> REFEREE_MESSAGE::PLAY_ON
     */
    REFEREE_MESSAGE &parseReferee(const std::string &message, REFEREE_MESSAGE &hear)
    {
      auto hear_message = splitInWords(message);
      if (hear_message.size() < 4)
      {
        throw new std::runtime_error("Invalid hear message" + message);
      }

      if (hear_message.at(2) != "referee")
      {
        throw new std::runtime_error("Invalid referee message" + message);
      }

      auto themessage = hear_message[3];
      // [ "hear", "200", "referee", "play_on" ]
      if (themessage == "play_on")
      {
        hear = REFEREE_MESSAGE::PLAY_ON;
      }
      else if (themessage == "drop_ball")
      {
        hear = REFEREE_MESSAGE::DROP_BALL;
      }
      else
      {
        hear = REFEREE_MESSAGE::UNKNOWN;
        cout << "Referee message not recognized: " << message << endl;
      }
      return hear;
    }
  }
}
