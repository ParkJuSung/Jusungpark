using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WorldScript : MonoBehaviour {

        float minSwipeDist;
        Vector2 SwipeDirection;
    bool Swiped = false;

    void Awake()
    {
        Vector2 ScreenSize = new Vector2(Screen.width,Screen.height);
        minSwipeDist = Mathf.Max(ScreenSize.x, ScreenSize.y) / 14f;
    }

    void Update()
    {
        ProcessInput();
    }


    Vector3 MouseDownPos;

    void ProcessInput()
    {
        if (Input.GetMouseButtonDown(0))
        {
            MouseDownPos = Input.mousePosition;
            Swiped = true;
        }
        else if (Input.GetMouseButton(0))
        {
            bool swipedected = CheckSwipe(MouseDownPos, Input.mousePosition);
            SwipeDirection = (Input.mousePosition - MouseDownPos).normalized;

            if (swipedected)
                OnSwipeDeteced(SwipeDirection);
        }
        else if (Input.GetMouseButtonUp(0))
            Swiped = true;
    }

    private bool isInputBlocked = false;

    bool CheckSwipe(Vector3 MouseDownPos, Vector3 CurrentPos)
    {
        if (Swiped)
            return false;

        if(isInputBlocked)
        return false;

        Vector2 currentSwipe = CurrentPos - MouseDownPos;

        if(currentSwipe.magnitude >= minSwipeDist)
        {
            return true;
        }

        return false;
    }

    void OnSwipeDeteced(Vector2 SwipeDirection)
    {
        Swiped = true;
    }

    void blockinput()
    {
        isInputBlocked = true;
    }

    void UnBlockInput()
    {
        isInputBlocked = false;
    }
}
