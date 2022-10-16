# 单向链表
+ Fang XS.
+ 1452512966@qq.com
+ 如果有错误，希望被指出，学习技术的路难免会磕磕绊绊。
## 关于`list.c` `list.h`模块
### 简介
+ 链表是一种常用数据结构。
+ `list.c` `list.h`模块是`C`风格的面向对象思想。
+ 链表的基本操作
    + 链表的初始化、插入、删除、查找、修改等。
### 抽象数据类型（ADT）
1. 建立抽象
    + 类型名
      + 单向链表
    + 类型属性
      + 链表项
        1. 数据域
        2. 指针域
    + 类型操作
      1. 初始化链表为空
      2. 判断是否为空
      3. 判断是否为满
      4. 取链表项项数
      5. 添加链表项
      6. 删除链表项
      7. 遍历链表，处理链表项
      8. 清空链表
2. 建立接口
    + 数据的表示
    + ADT操作的函数
3. 实现接口
    + C方法是把函数定义放在源文件中，整个模块由`list.c` `list.h`组成。
    + `list.h`属性和对数据的操作（即函数）的声明。
    + `list.c`函数实现，模块内部函数使用`static`关键字限定，不声明在头文件中。
### 关于程序
1. **属性**
   + 一个链表节点包括数据域和指针域;
   + 数据域用结构体```Item```封装，用来存放数据;
     ```c
        typedef struct ItemOfList{
           int a;
        }Item;
      ```
   + 节点结构体，数据域指针域的封装
     ```c
     /**< node >**/
     typedef struct node{
     Item item;
     struct node * next;
     }Node;
     ```
   + 链表头指针，指向一条链表
     ```c
     /**< list >**/
     typedef struct list{
       Node * Head;
     }List;
     ```
2. **函数**

| 函数名 |     `void InitList(List * pList);`      |
|----:|:---------------------------------------:|
|  功能 |                  初始化链表                  |
|  描述 |                  将链表置空                  |
|  形参 |              `pList` 目标链表               |
| 返回值 |                    无                    |

| 函数名 | `bool ListIsEmpty(const List * pList);` |
|----:|:---------------------------------------:|
|  功能 |                判断链表是否为空                 |
|  描述 |                    无                    |
|  形参 |              `pList` 目标链表               |
| 返回值 |               `true`为空链表                |
| 返回值 |              `false`不为空链表               |

| 函数名 | `bool ListIsFull(const List * pList);` |
|----:|:--------------------------------------:|
|  功能 |             判断是否还有空间创建新节点              |
|  描述 |           函数内部暂时没有对目标链表进行操作            |
|  形参 |              `pList` 目标链表              |
| 返回值 |                   无                    |

| 函数名 | `uint32_t ListItemCount(const List * pList);` |
|----:|:---------------------------------------------:|
|  功能 |                   获取链表中节点个数                   |
|  描述 |                  通过遍历链表进行计数                   |
|  形参 |                 `pList` 目标链表                  |
| 返回值 |                     节点的个数                     |

| 函数名 | `bool AddItem(List * pList, Item item);` |
|----:|:----------------------------------------:|
|  功能 |                 向链表添加节点                  |
|  描述 |                 在链表尾部添加                  |
|  形参 |               `pList` 目标链表               |
|  形参 |           `item`节点的数据域（值传递拷贝）            |
| 返回值 |                `true`添加成功                |
| 返回值 |             `false`堆内存不足添加失败             |

| 函数名 | `bool DelItem(List * pList, Item item);` |
|----:|:----------------------------------------:|
|  功能 |                 删除链表中节点                  |
|  描述 |           与`item`相同的节点（需要修改函数）           |
|  形参 |               `pList` 目标链表               |
|  形参 |           `item`节点的数据域（值传递拷贝）            |
| 返回值 |                `true`删除成功                |
| 返回值 |            `false`删除失败（基本不可能）            |

| 函数名 | `void EmptyTheList(List * pList);` |
|----:|:----------------------------------:|
|  功能 |               清理整个链表               |
|  描述 |              释放链表所有内存              |
|  形参 |            `pList` 目标链表            |
| 返回值 |                 无                  |

| 函数名 | `void Traverse(List * pList, void (*pFun)(Item item));` |
|----:|:-------------------------------------------------------:|
|  功能 |                  访问每个节点并执行`pFun`指向的函数                   |
|  描述 |                 `pFun`指向的函数作用于链表的每个节点一次                 |
|  形参 |                      `pList` 目标链表                       |
|  形参 |                       `pFun` 目标函数                       |
| 返回值 |                            无                            |

**特殊情况**
+ 在堆上申请内存。
+ 调用`ListDelete`后，最好不进行任何链表操作。
+ 调用`ListDelete`后，因为没有重新赋值实参，实参还是指向已经释放的内存。
+ 调用`ListDelete`后，需要重新使用链表先调用`ListCreate`函数且重新初始化。
+ 使用不当，会导致**segment fault**，所以未添加代码到源码。
```c
List * ListCreate(void){
    List * this = (List *) malloc(sizeof(List));
    InitList(this);
    return this;
}
```
| 函数名 | `List * ListCreate(void);` |
|----:|:--------------------------:|
|  功能 |       在堆上创建`List`对象        |
|  描述 | 会调用`InitList`函数进行初始化（最好不用） |
|  形参 |             无              |
| 返回值 |         `List *`对象         |

```c
void ListDelete(List * pList){
    EmptyTheList(pList);
    free(pList);
    /* warning: dangling pointer line130 */
    /*pList->Head = NULL;*/
    /* if not set NULL of line130:
    *  bug :
    *  [ListIsEmpty] return: 0
    *  dangling ptr point to random mem.
    */
}
```
| 函数名 |    `void ListDelete(List * pList);`    |
|----:|:--------------------------------------:|
|  功能 |             删除堆上的对象`pList`             |
|  描述 |   会调用`EmptyTheList`函数释放整个链表的内存（最好不用）   |
|  描述 | 调用`ListDelete`后实参为**dangling pointer** |
|  描述 |      调用`ListDelete`后再使用实参需要重新初始化       |
|  形参 |              `pList`目标链表               |
| 返回值 |                   无                    |
