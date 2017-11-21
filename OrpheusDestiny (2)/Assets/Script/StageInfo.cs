using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StageInfo  
{
    private static StageInfo instance = null;
    public static StageInfo Instance
    {
        get
        {
            if (instance == null)
                instance = new StageInfo();

            return instance;
        }
    }
    private StageInfo()
    {

    }

    struct StageDefault
    {
       public int BufAtk;
       public int BufDef;
       public int BufHp;
       public int GoblinCount;
       public int SkeletonCount;
    }



}
