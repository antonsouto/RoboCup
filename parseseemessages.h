#ifndef PARSEHEARMESSAGES_H
#define PARSEHEARESSAGES_H

#include "types.h"

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
  Player &parseHearMessage(const std::string &message, Player &player);

  namespace Hear

  {

    /**
     * Player the referee message from the hear message
     * @param message hear message from the server
     * @return REFEREE_MESSAGE
     * @example PlayerRefereeMessage("hear 200 referee play_on") -> REFEREE_MESSAGE::PLAY_ON
     */
    REFEREE_MESSAGE &parseReferee(const std::string &message, REFEREE_MESSAGE &hear);

  }
}

#endif // PARSEHEARESSAGES_H
