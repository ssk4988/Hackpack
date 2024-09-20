/**
 * Author: Sachin Sivakumar
 * Date: 2024-09-20
 * License: CC0
 * Source: https://codeforces.com/blog/entry/83467
 * Description: Allows updates to be processed like a queue where the earliest update is removed
 * Time: $O(TQ \log Q)$, where T is the time complexity of an update
 * Status: tested somewhat
 */
#pragma once

#include "RollbackUF.h"

RollbackUF uf(1);
using U = pii;
struct QueueUpdates {
    vector<tuple<bool, int, U>> st; // reversed, time before update, update
    void push(U u, bool r = false) {
        int t = uf.time();
        uf.join(u.first, u.second);
        st.emplace_back(r, t, u);
    }

    tuple<bool, int, U> rollback() {
        auto [r, t, u] = st.back();
        st.pop_back();
        uf.rollback(t);
        return {r, t, u};
    }
    
    void pop() {
        assert(sz(st));
        auto [r, t, u] = st.back();
        if (r) return void(rollback());
        array<vector<U>, 2> sq;
        int diff = 0; // stack - queue
        do {
            tie(r, t, u) = rollback();
            sq[r].push_back(u);
            diff += r ? -1 : 1;
        } while (sz(st) && diff > 0);
        if (sz(st) == 0) {
            for(auto &u : sq[0]) push(u, true); // turn all stack updates into queue updates
            sq[0].clear();
        }
        rep(i, 0, 2)
            while(sz(sq[i])) 
                push(sq[i].back(), i), sq[i].pop_back();
        rollback();
    }
};
