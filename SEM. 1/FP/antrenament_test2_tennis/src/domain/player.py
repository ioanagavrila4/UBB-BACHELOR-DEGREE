class Player:
    def __init__(self, id, name, playing_strength):
        self.id = id
        self.name = name
        self.strength = playing_strength

    def __str__(self):
        return "ID:" + str(self.id) + "Name: " + str(self.name) + "Player strength: " + str(self.strength)

    def id(self):
        return self.id

    def name(self):
        return self.name()

    def strength(self):
        return self.strength()




