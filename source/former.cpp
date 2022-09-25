#include <iostream>

const int MAX_N = 50; 
const unsigned int MAX_DIST = 2000000000;

int main()
{
    int n;
    char d[MAX_N];
    unsigned int x[MAX_N], y[MAX_N];

    unsigned int dist[MAX_N][MAX_N];   // 碰撞的距离（碰撞时间）
    unsigned int eat[MAX_N];

    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> d[i];
        std::cin >> x[i];
        std::cin >> y[i];
        // std::cout << d[i] << x[i] << y[i] << std::endl;
    }

    // 将所有牛能吃到的草初始化为无限大
    for (int i = 0; i < n; i++)
        eat[i] = MAX_DIST;

    // 标志出所有可能相撞的牛，及相撞距离(即碰撞时间)
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++) {
            dist[i][k] = MAX_DIST;
            // 如果是同一头牛，则跳过
            if (i == k) continue;

            // 如果i是北向，k是东向
            if (d[i]=='E' && d[k]=='N') {
                // printf("%d(%c, %d, %d), %d(%c, %d, %d)\n\n", i, d[i], x[i], y[i], k, d[k], x[k], y[k]);
                if (x[k]>x[i] && y[k]<=y[i] && y[i]-y[k] < x[k]-x[i]) {
                    dist[i][k] = x[k] - x[i];
                }
            }

            // 如果i是东向，k是北向
            if (d[i]=='N' && d[k]=='E') {
                // printf("%d(%c, %d, %d), %d(%c, %d, %d)\n\n", i, d[i], x[i], y[i], k, d[k], x[k], y[k]);
                if (x[k]<=x[i] && y[k]>y[i] && x[i]-x[k] < y[k]-y[i]) {
                    dist[i][k] = y[k] - y[i];
                }
            }
        }

    bool found = false;
    unsigned int min = MAX_DIST;
    unsigned int min_i, min_k;
    while (1) {
        // 查找最小碰撞牛i和牛k
        min = MAX_DIST;
        found = false;
        for (int i = 0; i < n; i++)
            for (int k = 0; k < n; k++) {
                if (dist[i][k] < min) {
                    found = true;
                    min = dist[i][k];
                    min_i = i;
                    min_k = k;
                }
            }
        // 如果未找到碰撞的牛i和牛k，则退出循环
        if (!found)  break;

        // 将牛i的吃草值设置为碰撞时的值
        eat[min_i] = min;
        dist[min_i][min_k] = MAX_DIST;

        for (int i = 0; i < n; i++) {
            // 将原来被牛i碰撞其他牛的设置为不碰撞
            dist[min_i][i] = MAX_DIST;
            // 与牛i碰撞的牛需要重新计算是否还会碰撞
            if(dist[i][min_i]==MAX_DIST) continue;
            if(d[min_i]=='E') {
                if(x[min_k]-x[min_i]>x[i]-x[min_i]) continue;
            }
            else if(y[min_k]-y[min_i]>y[i]-y[min_i]) continue;
            dist[i][min_i] = MAX_DIST;
        }

    }

    for(int i = 0; i < n; i++) {
        if (eat[i] == MAX_DIST) {
            std::cout << "Infinity" << std::endl;
        } else {
            std::cout << eat[i] << std::endl;
        }
    }

}