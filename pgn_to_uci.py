import chess

openingFile = open("openingsGeneralNotations.txt",'r')
writingFile = open("openingsUCInotation.txt",'w')
openings = openingFile.readlines()

UCIopenings = []
line =1
for opening in openings:
    if(len(opening)>1):
        if opening[0]!='[':
            if opening[0]=='1' and opening[1]=='.':
                opening = opening[0:len(opening)-1]+" "
                UCIopenings.append(opening+"\n")
            else:
                prev = UCIopenings.pop()
                if opening[0]!=' ' and prev[len(prev)-2]!=' ':
                    opening=" "+opening
                UCIopenings.append(prev[0:len(prev)-1] + opening)

# writingFile.writelines(UCIopenings)
finalOpenings = []

for opening in UCIopenings:
    moves = opening.split(' ')
    for i in moves:
        if i[0]>='1' and i[0]<='9':
            moves.remove(i)
    ref = moves.pop()
    if(len(ref)>1 and ref[len(ref)-1]=='\n'):
        moves.append(ref[0:len(ref)-1])
    elif len(ref)>1 :
        moves.append(ref )
    # print(moves)

    board = chess.Board()
    UCIopening = ""
    for move in moves:
        UCIopening+=str(board.parse_san(move))
        board.push(board.parse_san(move))
        UCIopening+=' '
    print(UCIopening)
    finalOpenings.append(UCIopening+'\n')

writingFile.writelines(finalOpenings)
