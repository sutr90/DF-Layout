from random import randint, choice, random
from copy import deepcopy
from math import exp
import time

class State:
	def __init__(self, ws):
		self.workshops = ws
		self.deltas = [(0,1),(1,0),(0,-1),(-1,0)]

	def swapWorkshops(self, w1, w2):
		w1, w2 = w2, w1

	def getArea(self):
		x = [p.pos[0] for p in self.workshops]
		y = [p.pos[1] for p in self.workshops]

		maxX,maxY = max(x), max(y)
		minX,minY = min(x), min(y)
		return (maxX-minX)*(maxY-minY)

	def getOverlap(self):
		total = 0
		gen = [(a, b) for a in self.workshops for b in self.workshops]
		for wp in gen:
			if wp[0].pos == wp[1].pos:
				total += 1000
		return total

	def getDistances(self):
		total = 0
		gwi = lambda _: self.workshops[_-1]
		gen = ((w1, w2) for w1 in self.workshops for w2 in [gwi(wi) for wi in w1.nbs])
		dist = lambda x: abs(x[0].pos[0]-x[1].pos[0]) + abs(x[0].pos[1]-x[1].pos[1])
		return sum([dist(w) for w in gen])

	def getCost(self):
		a = self.getArea()
		d = self.getDistances()
		o = self.getOverlap()
		return a + d + o

	def transition(self):
		if randint(0,3) == 0:
			self.swapWorkshops(choice(self.workshops), choice(self.workshops))
		else:
			w=choice(self.workshops)
			w.moveRel(choice(self.deltas))

class Workshop:
	def __init__(self, x, y, nbs):
		self.pos=(x,y)
		self.nbs=nbs

	def moveRel(self, delta):
		self.pos = (self.pos[0] + delta[0],self.pos[1] + delta[1])

class Annealing:
    def __init__(self):
        ws = [Workshop(0,0,[]),
        Workshop(0,0,[2,3]),
        Workshop(0,0,[3,2,5,6,7]),
        Workshop(0,0,[4,14,15]),
        Workshop(0,0,[5,3,11,6]),
        Workshop(0,0,[6,5,7,3,9]),
        Workshop(0,0,[7,3,9,6]),
        Workshop(0,0,[]),
        Workshop(0,0,[9,6,7]),
        Workshop(0,0,[10,11,16,19,27]),
        Workshop(0,0,[11,5,10]),
        Workshop(0,0,[]),
        Workshop(0,0,[13,27]),
        Workshop(0,0,[14,4,20]),
        Workshop(0,0,[15,16,22,4]),
        Workshop(0,0,[16,20,10,17,15]),
        Workshop(0,0,[17,22,16]),
        Workshop(0,0,[18,21,26]),
        Workshop(0,0,[19,21,10]),
        Workshop(0,0,[20,16,25,14]),
        Workshop(0,0,[21,25,27,23,24,19,18]),
        Workshop(0,0,[22,17,15]),
        Workshop(0,0,[23,21]),
        Workshop(0,0,[24,21,28]),
        Workshop(0,0,[25,20,21]),
        Workshop(0,0,[26,18]),
        Workshop(0,0,[27,13,21,28,10]),
        Workshop(0,0,[28,24,27])
        ]
        self.state = State(ws)

    def doWork(self):
        t = 1.0
        iter = 500
        step_count = 0
        for step in range(1000):
            cost = self.state.getCost()
            for i in range(iter):
                step_count += 1
                newState = deepcopy(self.state)
                newState.transition()
                newCost = newState.getCost()
                if newCost <= cost:
                    self.state = newState
                    cost = newCost
                    best_state = deepcopy(self.state)
                elif exp(-(newCost - cost)/t) > random():
                    cost = newCost
                    best_state = deepcopy(self.state)
            t *= 0.95
            if step % 500 == 0:
                print([step, t])

        return best_state

def main():
	an = Annealing()
	ws, c = an.doWork()
	print(c)
	for w in ws:
		print(w.pos)

if __name__ == '__main__':
	start_time = time.time()
	main()
	print(time.time() - start_time, "seconds")










