using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SOwn
{

    private static SOwn instance = null;
    public static SOwn Instance
    {
        get
        {
            if (instance == null)
                instance = new SOwn();

            return instance;
        }
    }
    private SOwn()
    {

    }
    public List<Unit> UnitList = new List<Unit>(); // 전체 영웅 저장용도
}
