using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Kakao : MonoBehaviour {

    BoardManager board = new BoardManager();
    // Use this for initialization
    void Start () {
        Debug.Log("Test Board");
        Debug.Log("Before update Board");
        board.ShowBoard();
        board.UpdateBoard();
        Debug.Log("After update Board");
        board.ShowBoard();
        Debug.Log("Random data board");
        board.InData();
        Debug.Log("Before update Board");
        board.ShowBoard();
        board.UpdateBoard();
        Debug.Log("After update Board");
        board.ShowBoard();
    }
	
	// Update is called once per frame
	void Update () {
		
	}
}


