from pokemon import Trainer, Pokemon, TeamRocket
            
sacha = Trainer()

try:
    with open("world.txt", "r") as f:
        world = f.read()
except Exception:
    print("ERROR : no world.txt file found, exiting ...")
    sys.exit()

try:
    sacha.encounter(world)
    Pokemon.infos()
    TeamRocket.infos()
except Exception as e:
    print(e)
