from itertools import count

from src.domain.player import Player
import os
class Player_Repository:
    def __init__(self):
        self.__all_players = []
        self.get_from_text_file()

    def get_all_players(self):
        return self.__all_players
    def add_player_repo(self, player):
        self.__all_players.append(player)
    def get_from_text_file(self):
        with open("repository/players.txt", "r") as file:
            rows = file.readlines()
        for row in rows:
            (id, name, strength) = [item.strip() for item in row.split(",")]
            self.add_player_repo(Player(int(id), name, int(strength)))
