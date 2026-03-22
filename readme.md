虛擬碼：    
```
1.run數：   
    2.初始化出NP個D維度向量，並將他們用ackyle func.計算   
    3.當(目前次數<Evaluation times)：   
        a.對每個向量(NP個)做DE步驟:         
            - Mutation   
            - Crossover   
            - Selection   
            - 重新計算ackyle func.，與原結果比較，較佳就替換   
    5.從NP個向量中找出最小(也指最佳近似解)    
6.找出所有run的最佳近似解中的最佳&計算其平均    
```

---
test01：
![image](https://github.com/xuanlai710/DE_Ackyle/blob/main/TEST3.png)

