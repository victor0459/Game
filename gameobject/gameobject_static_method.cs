using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class lesson5 : MonoBehaviour
{
    //准备用来克隆的对象
    //1直接是场景上的某个对象
    //2可以是一个预设体对象
    public GameObject myobj;
    // Start is called before the first frame update
    void Start()
    {
        //知识点一 gameobject中的成员遍历
        //名字
        print(this.gameObject.name);
        //修改名字
        this.gameObject.name = "lesson_plus";
        print(this.gameObject.name);
        //是否激活
        print(this.gameObject.activeSelf);//true激活
        //是否是静态
        print(this.gameObject.isStatic);
        //层级 layer
        print(this.gameObject.layer);
        //标签
        print(this.gameObject.tag);
        //transform
        print(this.gameObject.transform.position);

        //知识点二 gameobject中的静态方法
        //创建自带几何体
        GameObject obj=GameObject.CreatePrimitive(PrimitiveType.Cube);
        obj.name = "米菲创建的立方体";
        //只要得到一个gameobject对象 我们就可以得到它身上任何脚本信息
        //通过obj.GetCompent来得到


        //查找对象相关的知识
        //1查找单个对象

        /*  两种找单个对象的共同点:
         *  1.无法找到失活的对象
         *  2.如果场景中 存在多个满足条件的对象 我们无法准确的找到谁
         */
        //1通过对象名查找
        //这个查找比较低下 因为他会在场景中所有对象去查找
        
        GameObject obj2 = GameObject.Find("米菲");
        if (obj2 != null)
        {
            print(obj2.name);
        }
        else
        {
            print("没有找到");
        }
        //1.2通过标签查找对象
        //GameObject obj3 = GameObject.FindWithTag("Player");
        GameObject obj3 = GameObject.FindGameObjectWithTag("Player");//此方法同上面的方法一样
        if (obj3 != null)
        {
            print("根据tab找的对象"+obj3.name);
        }
        else
        {
            print("根据tab没有找到对象");
        }
        //2查找多个对象
        //只能找到激活对象
        GameObject[] obj4 = GameObject.FindGameObjectsWithTag("Player");
        print("找到tag为player对象的个数:" + obj4.Length);

        //它可以找到场景中挂载的某一个脚本对象
        //效率更低 上面的gameobject.find和findwithTag只是遍历对象
        //这个方法 不仅要遍历对象 还要遍历对象身上挂载的脚本
        lesson5 o = GameObject.FindObjectOfType<lesson5>();
        print(o.gameObject.name);

        //重点  1实例化对象 克隆对象 的方法
        //作用是根据一个gameobject对象 创建处一个和它一模一样的方法
        GameObject obj5=GameObject.Instantiate(myobj);
        //以后学了更多的知识点 就可以在这操作obj5
        //如果继承了MonoBehaviour 可以不用写GameObject   Instantiate(myobj);
        //2删除对象
        GameObject.Destroy(obj5);
        GameObject.Destroy(obj5, 5);//第二个参数代表延迟几秒删除
        //此方法还可以删除脚本
        //此方法不会马上删除  一般下一帧才从内存移除
        //建议使用此方法 因为是异步 降低卡顿的几率
        GameObject.Destroy(this);
        //此方法立即删除
        GameObject.DestroyImmediate(obj5);

        //3过场景不移除 只要切换场景 对象会自动移除
        //不移除 使用以下方法
        //一般都是传 依附的GameObject对象
        GameObject.DontDestroyOnLoad(this.gameObject);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}

