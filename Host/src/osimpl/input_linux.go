// +build linux

package osimpl

//#cgo LDFLAGS: -lX11 -lXtst -lXext
//#include "input_linux.c"
import "C"
import "fmt"

// ! @ # $ % ^ & * ( ) { | } < > ? " + :
var keys = [...]rune{33, 64, 35, 36, 37, 94, 38, 42, 40, 41, 123, 124, 125, 60, 62, 63, 34, 43, 58}

func SendKeycode(keyCode uint8) {
	C.SendKeycode(C.int(keyCode))
}

func SendKeyboardString(toSend string) {
	for _, s := range []rune(toSend) {
		sendKeyboardRune(s)
	}
}

func sendKeyboardRune(toSend rune) {
	fmt.Println("toSend ", toSend)
	for _, key := range keys {
		if toSend == key {
			C.SendKeysymWithShiftKey(C.int(toSend))
			return
		}
	}

	switch {
	case 65 <= toSend && toSend <= 90: // A-Z
		C.SendKeysymWithShiftKey(C.int(toSend))
	default:
		C.SendKeysym(C.int(toSend))
	}
}

func MoveMouse(X, Y int) {
	C.SendMouseMove(C.int(X), C.int(Y))
}

func LeftClick() {
	LeftDown()
	LeftUp()
}

func RightClick() {
	RightDown()
	RightUp()
}

func LeftDown() {
	C.SendClick(1, 1)
}

func RightDown() {
	C.SendClick(3, 1)
}

func LeftUp() {
	C.SendClick(1, 0)
}

func RightUp() {
	C.SendClick(3, 0)
}

func MiddleDown() {
	C.SendClick(2, 1)
}

func MiddleUp() {
	C.SendClick(2, 0)
}

func ScrollDown() {
	C.SendClick(5, 1)
	C.SendClick(5, 0)
}

func ScrollUp() {
	C.SendClick(4, 1)
	C.SendClick(4, 0)
}

func VolumeDown() {
	C.SendKeysym(C.int(0x1008ff11))
}

func VolumeUp() {
	C.SendKeysym(C.int(0x1008FF13))
}
