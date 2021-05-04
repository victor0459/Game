using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class lesson11 : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        //知识点一 世界坐标系转本地坐标
        //世界坐标系转本地坐标系 可以帮助我们大概判断一个相对位置
        print(Vector3.forward);
        //世界坐标系 转换为本地坐标系的点
        //受到缩放scale影响
        print("转换后的点:"+this.transform.InverseTransformPoint(Vector3.forward));
        //世界坐标系方向 转换为本地坐标系的方向
        //受到缩放scale影响
        print("转换后的方向:" + this.transform.InverseTransformDirection(Vector3.forward));
        //受缩放影响的
        print("转换后的方向(受缩放影响):" + this.transform.InverseTransformVector(Vector3.forward));

        //知识点二 本地坐标系转世界坐标
        //本地坐标系的点转为相对世界坐标系的点 受缩放影响
        print("本地转世界点" + this.transform.TransformPoint(Vector3.forward));
        //本地坐标系的方向 转换为相对世界坐标系的方向 不受缩放影响
        print("本地转世界点" + this.transform.TransformDirection(Vector3.forward));
        //本地坐标系的方向 转换为相对世界坐标系的方向 受缩放影响
        print("本地转世界点" + this.transform.TransformVector(Vector3.forward));

    }

    // Update is called once per frame
    void Update()
    {
        
    }
}

