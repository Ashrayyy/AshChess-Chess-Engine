import chess

openingFile = open("openings.txt",'r')
openings = openingFile.readlines()

line = 0
for opening in openings:
    line+=1
    board = chess.Board()
    # if opening[0:len(opening)-2]!=' ':
    #     opening = opening[0:len(opening)-1]+" \n"
    moves = opening.split(' ')
    for move in moves:
        if(len(move)<=1):
            break
        if move[len(move)-1]=='\n':
            move=move[0:len(move)-1]
        print(move)
        board.push(board.parse_uci(move))
        # print(board)
        # try:
        #     board.push(board.parse_uci(move))
        # except:
        #     print(line)
    