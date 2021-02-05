## P1 认实headers、版本、重要资源
1. ```using namespace std;```
2. ```using std::cout;```
3. 重要网站
   - www.cplusplus.com
   - en.cppreference.com
   - gcc.gnu.org
<br><br>

## P2 STL体系结构基础
1. STL六大部件
   - 容器 Containers
   - 分配器 Allocators
   - 算法 Algorithms
   - 迭代器 Iterators
   - 适配器 Adapters
   - 仿函式 Functors
   ```c++
   #include<vector>
   #include<algorithem>
   #include<functional>
   #include<iostream>

   using namespace std;

   int main(){
       int ia[6] = {27, 210, 12, 47, 109, 83};
       vector<int,allocator<int>> vi(ia, ia+6);
       cout << cout_if(vi.begin(), vi.end(), not1(bind2nd(less<int>(), 40))) << endl;
       return 0;
   }
   ```
2. 复杂度,Complexity,O()
3. range-based for statement
4. auto
<br><br>

## P3 容器之分类与各种测试（一）
1. 结构与分类
   - 顺序容器 Sequence Container
      - Array 固定大小
      - Vector 后端扩充
      - Deque 前后均可扩充
      - List 双向链表
      - Forward-List 单向链表
   - 关联容器 Associative Containers
      - 有序容器
         - Set / Multiset
         - Map / Multimap
      - 无序容器
         - Unordered Set / Multiset
         - Unordered Map / Multimap
<br><br>

## P4 容器之分类与各种测试（二）