import sys 

def main(argc, argv):
    if argc < 3:
        print("Utilisation : python get.py GRAPHE NOM_STATION")
        sys.exit()
    nom = argv[2].upper()
    with open(argv[1]) as f:
        for line in f:
            print(line)
            nom_f = " ".join(line.split(" ")[1:])
            if nom in nom_f.upper():
                print(line)

if __name__ == "__main__":
    main(len(sys.argv), sys.argv)
