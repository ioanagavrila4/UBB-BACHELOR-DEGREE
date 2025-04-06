import random

from src.domain.player import Player
from src.repository.repo import Player_Repository
from src.service.services import Player_Service

class UI:
    def __init__(self):
        self.__player_service = Player_Service()

    def print_players(self, players):
        for player in players:
            print(player)
        print()

    def play_tournament(self, players):
        rounds = len(players)
        while rounds > 1:
            print("Last " + str(int(rounds)))
            self.print_players(players)

            rounds = rounds // 2
            random.shuffle(players)
            winners = []
            for i in range(0, len(players), 2):
                print("Current game: " + str(players[i]) + " vs " + str(players[i+1]) + "\n")

                winner_input = int(input("1. Choose what player wins: 1/2: "))
                if winner_input == 1:
                    players[i].strength += 1
                    winners.append(players[i])
                elif winner_input == 2:
                    players[i+1].strength += 1
                    winners.append(players[i+1])
                else:
                    raise Exception("Invalid Input. ")
            players = winners
        print("Winner is: " + str(players[0]))

    def players_winning_qualification(self, players):
        random.shuffle(players)

        winners = []
        for i in range(0, len(players), 2):
            print("Current game: " + str(players[i]) + " vs " + str(players[i + 1]) + "\n")

            client_input = input("1. Player 1 wins\n2.Player 2 wins\n")
            if client_input == "1":
                players[i].strength += 1
                winners.append(players[i])
            elif client_input == "2":
                players[i + 1].strength += 1
                winners.append(players[i + 1])
            else:
                raise Exception("Invalid input.")
        return winners

    def menu(self):
        while True:
            print("1. Display all players from the input file, sorted descending by strength")
            print("2. Play the qualifying rounds and play tournament")
            client_input = int(input("Choose a command: "))
            if client_input == 1:
                all_players_sorted_by_strength = self.__player_service.sort_all_by_strength()
                for player in all_players_sorted_by_strength:
                    print(player)
            elif client_input == 2:
                try:
                    all_players = self.__player_service.get_all_data()
                    if len(all_players) & (len(all_players) - 1) == 0:
                        print("No qualification needed!")
                        self.play_tournament(all_players)
                    else:
                        players_that_play_qualification = self.__player_service.player_playing_qualification()
                        print("Player for qualification round are: ")
                        self.print_players(players_that_play_qualification)

                        players_winning = self.players_winning_qualification(players_that_play_qualification)
                        print("Players that won: ")
                        self.print_players(players_winning)

                        print("Final lis of players: ")
                        tournament_players = self.__player_service.get_final_list_for_tournament(players_winning)
                        self.print_players(tournament_players)
                        print("Tournament begins!! ")
                        self.play_tournament(tournament_players)
                except Exception as ex:
                    print(str(ex))
            else:
                print("Invalid command!! ")





