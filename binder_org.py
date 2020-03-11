# A collection organizer.
#
# This was made with the intention of organizing music sheets.
# Here is a use case:
#
# $ cat sheets.txt
#
# Four, Miles Davis
# Sugar, Stanley Turrentine
# Chega de Saudade, Tom Jobim
# Four Brothers, Jimmy Giuffre
# Garota de Ipanema, Tom Jobim
# The Chase, Dexter Gordon
# In a Sentimental Mood, Duke Ellington
# Dexterity, Dexter Gordon
# Desafinado, Tom Jobim
# Estamos Aí, Maurício Einhorn
# Cheesecake, Dexter Gordon
# Batida Diferente, Maurício Einhorn
# Strasbourg St. Denis, Roy Hargrove
#
# $ python3
# >>> from binder_org import *
# >>> B = Binder.loadtxt("sheets.txt")
# >>> B.print()
# ... This will print a binder organized by Author
# >>> B = Binder.loadtxt("sheets.txt", SortName)
# >>> B.print()
# ... This will print a binder organized by Name (alphabetical)

import sys
import pickle
import numpy as np

def SortName(e):
  return e.name[0].lower

def SortAuthor(e):
  return e.author.lower

class Sheet:
  name = None
  author = None

  def __init__(self, name, author):
    self.name = name.lower().strip()
    self.author = author.lower().strip()

  @staticmethod
  def loadtxt(filename):
    S = np.genfromtxt(filename, dtype=np.unicode_, delimiter=',')
    R = []
    for s in S:
      R.append(Sheet(s[0], s[1]))
    return R

class Sleeve:
  sheets = None

  def __init__(self):
    self.sheets = []

  def add(self, s):
    self.sheets.append(s)

  def sort(self):
    self.sheets.sort(key=lambda e: e.name.lower())

  def len(self):
    return len(self.sheets)

  def print(self):
    for i, s in enumerate(self.sheets):
      print(f'  {i+1:d}: {s.name.title():s} by {s.author.title():s}')
    print('')

class Binder:
  sleeves = None
  titles = None
  n = None

  def __init__(self):
    self.sleeves = {}
    self.titles = []
    self.n = 0

  def add(self, s, k):
    if k not in self.sleeves:
      self.sleeves[k] = Sleeve()
      self.titles.append([k, self.sleeves[k]])
    self.sleeves[k].add(s)
    self.n += 1

  def sort(self, key=lambda e: e[0].lower(), reverse=False):
    self.titles.sort(key=key, reverse=reverse)

  def print(self, key=None, reverse=False):
    self.sort(key=key, reverse=reverse)
    print(f'Listing sleeves and their contents:\n  Titles: {self.n:d}\n'
          f'  Sleeves: {len(self.sleeves):d}\n')
    print('===================================')
    for i, T in enumerate(self.titles):
      t, s = T[0], T[1]
      s.sort()
      print(f'Sleeve {i+1:d}: {t.title():s} ({s.len():d} titles):\n---')
      s.print()

  def save(self, filename):
    with open(filename, 'wb') as out:
      pickle.dump(self, out, pickle.HIGHEST_PROTOCOL)

  @staticmethod
  def load(filename):
    with open(filename, 'rb') as inp:
      return pickle.load(inp)

  @staticmethod
  def loadtxt(filename, key=SortAuthor):
    B = Binder()
    S = Sheet.loadtxt(filename)
    for s in S:
      B.add(s, key(s)())
    B.sort()
    return B

if __name__ == "__main__":
  n = len(sys.argv)
  if n < 2 or n > 3:
    print(f'Usage: {sys.argv[0]:s} in_file [key]\n'
          f'  in_file - file containing titles and authors\n'
          f'  key     - whether to sort by \'author\' or \'name\'')
    sys.exit(1)
  key = SortAuthor
  if n == 3 and sys.argv[2] == 'name':
    key = SortName
  B = Binder.loadtxt(sys.argv[1], key)
  B.print()
