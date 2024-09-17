#include <iostream>
using namespace std;

template<typename T>
class DOUBLY_LL {
public:
    class NODE {
    public:
        NODE* next;
        NODE* prev;
        T data;

        NODE(T val) : data(val), next(nullptr), prev(nullptr) {}
    };

    NODE* head;
    NODE* tail;
    NODE* cursor;

    DOUBLY_LL() : head(nullptr), tail(nullptr) {
        cursor = new NODE('|'); // Cursor represented by "|"
        head = cursor;
        tail = cursor;
    }

    // Insert a character to the left of the cursor
    void INSERT(T element) {
        NODE* newnode = new NODE(element);

        if (cursor->prev == nullptr) {  // If cursor is at the head
            newnode->next = cursor;
            cursor->prev = newnode;
            head = newnode;
        } else {
            newnode->next = cursor;
            newnode->prev = cursor->prev;
            cursor->prev->next = newnode;
            cursor->prev = newnode;
        }
    }

    // Delete the character to the left of the cursor
    void DELETE() {
        if (cursor->prev == nullptr) {
            cout << "Nothing to delete." << endl;
            return;
        }

        NODE* toDelete = cursor->prev;
        if (toDelete->prev == nullptr) {  // If deleting the head
            head = cursor;
            cursor->prev = nullptr;
        } else {
            toDelete->prev->next = cursor;
            cursor->prev = toDelete->prev;
        }
        delete toDelete;
    }

    // Move cursor left
    void moveLeft() {
        if (cursor->prev != nullptr) {
            cursor = cursor->prev;
        }
    }

    // Move cursor right
    void moveRight() {
        if (cursor->next != nullptr) {
            cursor = cursor->next;
        }
    }

    // Print the content of the sentence
    void print() {
        NODE* current = head;
        while (current != nullptr) {
            cout << current->data;
            current = current->next;
        }
        cout << endl;
    }
};

// Class to manage multiple sentences (paragraph)
class Notepad {
public:
    class SentenceNode {
    public:
        SentenceNode* next;
        SentenceNode* prev;
        DOUBLY_LL<char> sentence;

        SentenceNode() : next(nullptr), prev(nullptr) {}
    };

    SentenceNode* head;
    SentenceNode* tail;
    SentenceNode* currentSentence;

    Notepad() : head(nullptr), tail(nullptr) {
        // Start with a single sentence
        SentenceNode* firstSentence = new SentenceNode();
        head = firstSentence;
        tail = firstSentence;
        currentSentence = firstSentence;
    }

    // Add a new character to the current sentence
    void addCharacter(char c) {
        currentSentence->sentence.INSERT(c);
    }

    // Remove a character from the current sentence
    void removeCharacter() {
        currentSentence->sentence.DELETE();
    }

    // Move cursor left in the current sentence
    void moveCursorLeft() {
        currentSentence->sentence.moveLeft();
    }

    // Move cursor right in the current sentence
    void moveCursorRight() {
        currentSentence->sentence.moveRight();
    }

    // Move cursor up (to the previous sentence)
    void moveCursorUp() {
        if (currentSentence->prev != nullptr) {
            currentSentence = currentSentence->prev;
        }
    }

    // Move cursor down (to the next sentence)
    void moveCursorDown() {
        if (currentSentence->next != nullptr) {
            currentSentence = currentSentence->next;
        }
    }

    // Add a new sentence (similar to hitting Enter)
    void addSentence() {
        SentenceNode* newSentence = new SentenceNode();
        if (tail == nullptr) { // First sentence case
            head = newSentence;
            tail = newSentence;
            currentSentence = newSentence;
        } else { // Add to the end
            tail->next = newSentence;
            newSentence->prev = tail;
            tail = newSentence;
            currentSentence = newSentence;
        }
    }

    // Print the entire notepad (all sentences)
    void printNotepad() {
        SentenceNode* current = head;
        while (current != nullptr) {
            current->sentence.print();
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    Notepad notepad;
    char input;

    while (true) {
        cout << "Enter a character to add, '9' to delete, '1' to move left, '2' to move right, '3' to move up,'7'to move down, '4' to add new sentence, or '5' to quit: ";
        cin >> input;

        if (input == '5') {
            break;
        } else if (input == '9') {
            notepad.removeCharacter();
        } else if (input == '1') {
            notepad.moveCursorLeft();
        } else if (input == '2') {
            notepad.moveCursorRight();
        } else if (input == '3') {
            notepad.moveCursorUp();
        } else if (input == '4') {
            notepad.addSentence(); // Add a new sentence
        }
        else if(input==7){
            notepad.moveCursorDown();
        }
         else {
            notepad.addCharacter(input);
        }

        notepad.printNotepad();
    }

    return 0;
}
