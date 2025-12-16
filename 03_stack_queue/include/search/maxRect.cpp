// 最大直方图

using Rank = unsigned int;

// 按定义蛮力地计算直方图H[]中的最大矩形（多个并列时取最靠左侧者）
long long mr_BRUTE( int H[], Rank n, Rank& mr_r, Rank& mr_s, Rank& mr_t ) { //蛮力：O(n^2)
    long long maxRect = 0;
    for ( Rank r = 0, s = 0, t = 0; r < n; r++, s = t = r ) {
        do s--; while ( (-1 != s) && (H[s] >= H[r]) ); s++;
        do t++; while ( (t < n) && (H[r] <= H[t]) );
        long long rect = (long long) H[r] * ( t - s );
        if ( maxRect < rect )
            { maxRect = rect; mr_r = r; mr_s = s; mr_t = t; }
    }
    return maxRect;
} //每个极大矩形耗时O(n)，累计O(n^2)



#include "Stack.hpp" //借助栈结构，计算直方图H[]中的最大矩形（并列时取最靠左者）

long long mr_STACK( int H[], Rank n, Rank& mr_r, Rank& mr_s, Rank& mr_t ) { //H[]皆非负
    Stack<Rank> SR; //次栈顶、栈顶总是s[r]-1与r，当前的t = t[r]
    long long maxRect = 0;
    for (Rank t = 0; t <= n; t++ ) { //逐个尝试以t为右边界的
        while ( !SR.empty() && ( t == n || H[SR.top()] > H[t] ) ) { //每一个极大矩形
            Rank r = SR.pop(), s = SR.empty() ? 0 : SR.top() + 1;
            long long mR = H[r] * ( t - s );
            if ( maxRect < mR )
                { maxRect = mR; mr_r = r; mr_s = s; mr_t = t; }
        }
        if ( t < n ) SR.push( t ); //栈中只记录所有的H[s] = min{ H[k] | s <= k <= t }
    } //assert: SR is empty at exit
    return maxRect;
} //每项进栈、出栈不过常数次，累计成本O(n)


//借助栈结构，计算直方图H[]中的最大矩形（并列时取最靠左者）
long long mr_STACKS( int H[], Rank n, Rank& mr_r, Rank& mr_s, Rank& mr_t ) { //除末项-1哨兵，H[]皆非负
    Rank* s = new Rank[n]; Stack<Rank> S; //自右可见项的秩
    for( Rank r = 0; r < n; r++ ) { //依次计算出
        while ( !S.empty() && ( H[S.top()] >= H[r] ) ) S.pop(); //每一个s(r)
        s[r] = S.empty() ? 0 : 1 + S.top();
        S.push(r);
    }
    while( !S.empty() ) S.pop();

    Rank* t = new Rank[n]; Stack<Rank> T; //自左可见项的秩
    for( Rank r = n-1; -1 != r; r-- ) { //依次计算出
        while ( !T.empty() && H[r] <= H[T.top()] ) T.pop(); //每一个t(r)
        t[r] = T.empty() ? n : T.top();
        T.push(r);
    }
    while( !T.empty() ) T.pop();

    long long maxRect = 0;
    for( Rank r = 0; r < n; r++ ) {
        long long mR = H[r] * (t[r] - s[r]);
        if ( maxRect < mR )
        { maxRect = mR; mr_r = r; mr_s = s[r]; mr_t = t[r]; }
    }
    delete [] s; delete [] t;
    return maxRect;
} //每项进栈、出栈不过常数次，累计成本O(n)