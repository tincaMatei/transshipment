#include "room.h"

int Room::getTransition() {
  return transition;
}

void RoomContext::pushRoom(Room* room) {
  rooms.push_back(room);
}

Room* RoomContext::getRoom(int roomId) {
  return rooms[roomId];
}
