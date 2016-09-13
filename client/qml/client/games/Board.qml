import QtQuick 2.5
import "./Chess/ChessBoard.js" as ChessBoard
import "Chess/"


Item {
    id: root

    property int cellSize: width / ChessBoard.BOARD_SIZE
    property int moveFromIndex: -1
    property int moveToIndex: -1

    height: parent.width
    width: parent.height

    function clear() {
        for (var i = 0; i < ChessBoard.BOARD_SIZE * ChessBoard.BOARD_SIZE; ++i) {
            pieceRepeater.itemAt(i).letter = ""
        }
    }

    function isWhiteSide(index) {
        var letter = getLetter(index);
        return letter === letter.toUpperCase();
    }

    function getLetter(index) {
        var letter = game.pieces[index];
        var res = letter;
        if (letter === 'b') {
            res = 'l';
        } else if (letter === 'B') {
            res = 'L';
        }
        return res;
    }



    Grid {
        id: cellGrid

        property int cellSize: parent.cellSize
        property Field selectedPiece: null

        anchors.fill: parent
        rows: ChessBoard.BOARD_SIZE
        columns: ChessBoard.BOARD_SIZE

        Repeater {

            id: repeater

            model: ChessBoard.BOARD_SIZE * ChessBoard.BOARD_SIZE

            DropArea {
                id: dropArea

                width: cellGrid.cellSize
                height: width

                onDropped: console.log("dropped")
                onEntered: console.log("entered")

                Rectangle {
                    id: cell

                    anchors.fill: parent
                    border.width: ChessBoard.BOARD_BORDER_WIDTH
                    border.color: ChessBoard.BOARD_BORDER_COLOR

                    color: (Math.floor(index / ChessBoard.BOARD_SIZE)
                        + (index % ChessBoard.BOARD_SIZE)) % 2
                            ? ChessBoard.CELL_DARK_COLOR : ChessBoard.CELL_LIGHT_COLOR

                    states: [
                        State {
                            when: dropArea.containsDrag
                            PropertyChanges {
                                target: cell
                                color: "grey"
                            }
                        }
                    ]

                }
            }

        }

    }

    Grid {
        id: piecesGrid

        anchors.fill: parent
        rows: ChessBoard.BOARD_SIZE
        columns: ChessBoard.BOARD_SIZE

        Repeater {
            id: pieceRepeater

            model: ChessBoard.BOARD_SIZE * ChessBoard.BOARD_SIZE

            Field {
                id: piece

                cellSize: cellGrid.cellSize
                whiteSide: isWhiteSide(index)
                letter: getLetter(index)
                pieceIndex: index
            }

        }

    }
    CloseButton{

    }

}

