虛擬碼：    
```
1.輸入 Run, Dimension, Population Size, F, CR數值    
2.執行run次：
    a.初始化出NP個D維度向量，計算其ackyle func值並紀錄為cost   
    b.(總共執行ackyle func.次數 < Evaluation times(D*10000))：  
        -對每個向量(NP個)做DE步驟:         
            - Mutation   
            - Crossover   
            - Selection   
            - 重新計算ackyle func.，與原結果比較，較佳就替換   
    c.找出本run的NP個向量中最小的cost(也指最佳近似解)    
3.找出所有run最佳近似解中的 最佳 & 計算平均值      
```
      
使用者須入Run, Dimension, Population Size, F, CR，若有數值錯誤或未輸入是無法使用的
![image](https://github.com/xuanlai710/DE_Ackyle/blob/main/img/warning.png)

---
TEST01：  
![image](https://github.com/xuanlai710/DE_Ackyle/blob/main/img/TEST1.png)   

TEST02：  
![image](https://github.com/xuanlai710/DE_Ackyle/blob/main/img/TEST2.png)   

TEST03：  
![image](https://github.com/xuanlai710/DE_Ackyle/blob/main/img/TEST3.png)   

