import random

from PIL.ImImagePlugin import number

from src.repository.repo import Player_Repository
from src.domain.player import Player

class Player_Service:
    def __init__(self):
        self.__data = Player_Repository()

    def get_all_data(self):
        return self.__data.get_all_players()
    def sort_all_by_strength(self):
        all_players = self.get_all_data()
        for i in range(0, len(all_players)):
            for j in range(i+1, len(all_players)):
                if all_players[i].strength < all_players[j].strength:
                    aux = all_players[i]
                    all_players[i] = all_players[j]
                    all_players[j] = aux
        return all_players

    def smaller_power_of_2(self, number):
        power = 1
        while power <= number:
            power = power*2
        return power//2

    def player_playing_qualification(self):
        all_players_sorted_increasing = self.sort_all_by_strength()
        all_players_sorted_increasing.reverse() #avem o lista sortata crescator cu jucatorii in functie de scor(cei mai slabi sunt primii


        total_players_allowed = (len(self.get_all_data()) - self.smaller_power_of_2(len(self.get_all_data()))) * 2 #cati jucatori trebuie sa joace in calificari
        player_that_play_qualification = all_players_sorted_increasing[0:total_players_allowed] #care-s jucatorii cei mai slabi care joaca
        return player_that_play_qualification

    def get_final_list_for_tournament(self, players_winning_qual):
        all_players_sorted_increasing = self.sort_all_by_strength() #toti jucatorii ordonati ca cei mai puternici sa fie primii
        all_players_sorted_increasing.reverse() #toti jucatorii ordonati crescator in functie de scor
        total_player_allowed = (len(self.get_all_data()) - self.smaller_power_of_2(len(all_players_sorted_increasing)))*2
        strongest_players = all_players_sorted_increasing[total_player_allowed:len(self.get_all_data())]

        for player in players_winning_qual:
            strongest_players.append(player)
        return strongest_players #astia sunt cei care intra direct in calificari

    def get_random_pairings(self, players):
        return random.shuffle(players)