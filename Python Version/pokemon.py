MAX_POKEBALL = 3

class Stat:
    def __init__(self, limit_to_base):
        self.base = None
        self.current = None
        self.limit_to_base = limit_to_base
    def in_bounds(self, lo, hi, val):
        if val < lo:
            return lo
        elif val > hi:
            return hi
        else:
            return val
    def set_base(self, value):
        self.base = value
        self.current = value
    def plus_base(self):
        self.base += 2
    def reset(self):
        self.current = self.base
    def modify(self, delta):
        self.current += delta
        if self.limit_to_base:
            self.current = self.in_bounds(0, self.base, self.current)
        else:
            self.current = self.in_bounds(0, 100, self.current)
    def to_string(self):
        return str(self.current) + "/" + str(self.base)

class WrongName(Exception):
    def __init__(self, n):
        self.n = n
    def __str__(self):
        return f"ERROR : encountered unknown Pokemon ({self.n}), exiting ..."

class NegativeLevel(Exception):
    def __init__(self, n):
        self.n = n
    def __str__(self):
        return f"ERROR : negative level for {self.n}, exiting ..."

class IncompleteStrategy(Exception):
    def __init__(self, name, in_strat):
        self.name = name
        self.in_strat = in_strat
    def __str__(self):
        s = f"ERROR : incomplete strategy for {self.name} ("
        while len(self.in_strat) > 0:
            s += self.in_strat[0]
            self.in_strat.pop(0)
            if len(self.in_strat) > 0:
                s += " "
        s += "), exiting ..."
        return s

class WrongStrategyNumber(Exception):
    def __init__(self, i, n):
        self.i = i
        self.n = n
    def __str__(self):
        return f"ERROR : wrong strategy input for {self.n} ({self.i}), exiting ..."

class WrongStrategyChar(Exception):
    def __init__(self, n, inp):
        self.inp = inp
        self.n = n
    def __str__(self):
        s = ""
        for i in self.inp:
            s += self.inp[0]
            self.inp.pop(0)
            if len(self.inp) > 0:
                s += " "
        return f"ERROR : wrong strategy input for {self.n} ({s}), exiting ..."

class Attack:
    def __init__(self, power=0):
        self.power = power
    def get_damage(self, caster, target):
        if self.power == 0:
            return 0
        return int(max(self.power * (getattr(getattr(caster, "atk"), "current") * getattr(caster, "level") - getattr(getattr(target, "dfs"), "current") * getattr(target, "level")) / (100.0 * (getattr(caster, "level") + getattr(target, "level")) / 2.0), 0.0) + 1)
    def execute(self, caster, target):
        hp_loss = self.get_damage(caster, target)
        if getattr(caster, "hindered"):
            hp_loss = 0
            setattr(caster, "hindered", False)
        getattr(target, "hp").modify(-hp_loss)
        self.special_effect(caster, target, hp_loss)
        return caster, target
    def special_effect(self, caster, target, dmg):
        pass

class Ember(Attack):
    def __init__(self):
        super().__init__(20)

class Drain(Attack):
    def __init__(self):
        super().__init__(15)
    def special_effect(self, caster, target, dmg):
        getattr(caster, "hp").modify(int(0.5 * dmg + 1))

class Headbutt(Attack):
    def __init__(self):
        super().__init__(25)
    def special_effect(self, caster, target, dmg):
        getattr(caster, "hp").modify(-4)

class WaterCanon(Attack):
    def __init__(self):
        super().__init__(15)
    def special_effect(self, caster, target, dmg):
        getattr(target, "dfs").modify(-1)

class Sleep(Attack):
    def special_effect(self, caster, target, dmg):
        getattr(caster, "hp").modify(14)
        setattr(caster, "asleep", True)

class Snore(Attack):
    def special_effect(self, caster, target, dmg):
        getattr(target, "dfs").modify(-1)

class Reinforce(Attack):
    def special_effect(self, caster, target, dmg):
        getattr(caster, "dfs").modify(1)

class Roar(Attack):
    def special_effect(self, caster, target, dmg):
        getattr(caster, "atk").modify(1)

class SleepPowder(Attack):
    def special_effect(self, caster, target, dmg):
        setattr(target, "asleep", True)

class Growl(Attack):
    def special_effect(self, caster, target, dmg):
        getattr(target, "atk").modify(-1)

class Carapace(Attack):
    def special_effect(self, caster, target, dmg):
        getattr(caster, "dfs").modify(2)

class Protect(Attack):
    def special_effect(self, caster, target, dmg):
        setattr(target, "hindered", True)

class TeamRocket:
    stolen = []
    def __init__(self, p):
        self.stolen.append(p)
    @classmethod
    def infos(cls):
        print("Pokemon stolen by TeamRocket :")
        if len(cls.stolen) == 0:
            return
        for i in range(len(cls.stolen)):
            print("-", cls.stolen[i])

class Trainer:
    def __init__(self):
        self.pokemons = []
    def get_level(self, line, name):
        if len(line) == 0:
            print(f"WARNING : no level nor strategy given for {name} in input file, using level=1 and 0 1 2 as default strategy")
            line += ["0", "1", "2"]
            return 1
        else:
            lvl = int(line[0])
            if lvl < 0:
                raise NegativeLevel(name)
            line.pop(0)
            return lvl
    def read_from_file(self, input_line):
        line = input_line.strip().split()
        name = line[0]
        line.pop(0)
        
        if name == "Ronflex":
            p = Ronflex(self.get_level(line, name))
        elif name == "Dracofeu":
            p = Dracofeu(self.get_level(line, name))
        elif name == "Florizarre":
            p = Florizarre(self.get_level(line, name))
        elif name == "Tortank":
            p = Tortank(self.get_level(line, name))
        elif name == "TeamRocket":
            if len(self.pokemons) > 0:
                TeamRocket(self.pokemons[0])
                self.pokemons.pop(0)
            return True
        else:
            raise WrongName(name)
        if len(line) == 0:
            print(f"WARNING : no strategy given for {name} in input file, using 0 1 2 as default strategy")
            line += ["0", "1", "2"]
        p.read_strategy(line)
        p.setup()
        return p
    def encounter(self, in_file):
        print("Wandering in the high grass ...")
        lines = in_file.split("\n")
        for l in lines:
            p = self.read_from_file(l)
            if p == True:
                continue
            if len(self.pokemons) < MAX_POKEBALL:
                self.pokemons.append(p)
                print(" -- captured :", p)
                continue
            while True:
                self.pokemons[0].rest()
                win = self.pokemons[0].fight_with(p)
                if win:
                    print(" --", self.pokemons[0], "won against", p)
                    self.pokemons[0].level_up()
                    Pokemon.num_pok -= 1
                    break
                else:
                    print(" --", self.pokemons[0], "lost against", p)
                    p.reset()
                    self.pokemons.pop(0)
                    Pokemon.num_pok -= 1
                    if len(self.pokemons) == 0:
                        Pokemon.num_pok -= 1
                        break
                    
class Pokemon:
    num_pok = 0
    def __init__(self, name, level):
        self.strategy = []
        self.moves = []
        self.name = name
        self.level = level
        self.current_move = 0
        self.asleep = False
        self.hindered = False
        self.hp = Stat(True)
        self.atk = Stat(False)
        self.dfs = Stat(False)
        Pokemon.num_pok += 1
    def __eq__(self, other):
        return False
    @classmethod
    def infos(cls):
        print(f"Number of Pokemons in the area : {Pokemon.num_pok}")
    def is_ko(self):
        return self.hp.current == 0
    def setup(self):
        pass
    def rest(self):
        self.hp.reset()
        self.atk.reset()
        self.dfs.reset()
        self.current_move = 0
        self.asleep = False
        self.hindered = False
    def reset(self):
        self.atk.reset()
        self.dfs.reset()
        self.current_move = 0
        self.hindered = False
    def level_up(self):
        self.hp.plus_base()
        self.atk.plus_base()
        self.dfs.plus_base()
        self.level += 1
        self.hindered = False
    def __str__(self):
        return self.name + " (hp: " + self.hp.to_string() + ", atk: " + self.atk.to_string() + ", def: " + self.dfs.to_string() + ", lvl: " + str(self.level) + ")"
    def attack(self, other):
        if self.is_ko() or other.is_ko():
            return self, other
        if self.asleep:
            self.asleep = False
            return self, other
        self, other = self.moves[self.strategy[self.current_move]].execute(self, other)
        self.current_move += 1
        self.current_move %= len(self.moves)
        return self, other
    def fight_with(self, other):
        for _ in range(200):
            if self.is_ko() or other.is_ko():
                break
            self, other = self.attack(other)
            other, self = other.attack(self)
        return not self.is_ko()
    def read_strategy(self, input_strat):
        for i in range(min(3, len(input_strat))):
            if not input_strat[i].isnumeric():
                raise WrongStrategyChar(self.name, input_strat)
        if len(input_strat) < 3:
            raise IncompleteStrategy(self.name, input_strat)
        for _ in range(3):
            idx = int(input_strat[0])
            if idx < 0 or idx >= 3:
                raise WrongStrategyNumber(idx, self.name)
            self.strategy.append(idx)
            input_strat.pop(0)
        if len(input_strat) > 0:
            s = f"WARNING : ignoring additional strategy inputs for {self.name} ("
            while len(input_strat) > 0:
                s += input_strat[0]
                input_strat.pop(0)
                if len(input_strat) > 0:
                    s += " "
            s += ")"
            print(s)

class Ronflex(Pokemon):
    def __init__(self, level):
        super().__init__("Ronflex", level)
    def setup(self):
        self.hp.set_base(60)
        self.atk.set_base(45)
        self.dfs.set_base(30)
        self.moves.append(Headbutt())
        self.moves.append(Sleep())
        self.moves.append(Snore())

class Dracofeu(Pokemon):
    def __init__(self, level):
        super().__init__("Dracofeu", level)
    def setup(self):
        self.hp.set_base(50)
        self.atk.set_base(55)
        self.dfs.set_base(35)
        self.moves.append(Ember())
        self.moves.append(Reinforce())
        self.moves.append(Roar())

class Florizarre(Pokemon):
    def __init__(self, level):
        super().__init__("Florizarre", level)
    def setup(self):
        self.hp.set_base(45)
        self.atk.set_base(45)
        self.dfs.set_base(35)
        self.moves.append(Drain())
        self.moves.append(SleepPowder())
        self.moves.append(Growl())

class Tortank(Pokemon):
    def __init__(self, level):
        super().__init__("Tortank", level)
    def setup(self):
        self.hp.set_base(45)
        self.atk.set_base(40)
        self.dfs.set_base(35)
        self.moves.append(WaterCanon())
        self.moves.append(Carapace())
        self.moves.append(Protect())