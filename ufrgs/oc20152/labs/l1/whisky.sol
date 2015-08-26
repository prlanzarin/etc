Problem:    whisky
Rows:       28
Columns:    15
Non-zeros:  62
Status:     OPTIMAL
Objective:  lucro = 39888.88889 (MAXimum)

   No.   Row name   St   Activity     Lower bound   Upper bound    Marginal
------ ------------ -- ------------- ------------- ------------- -------------
     1 lucro        B        39888.9                             
     2 limitesImportacao[J]
                    NU          2000                        2000       7.77778 
     3 limitesImportacao[O]
                    NU          2500                        2500       3.33333 
     4 limitesImportacao[M]
                    NU          1200                        1200       13.3333 
     5 maxPercentagens[J,A]
                    B       -1017.78                          -0 
     6 maxPercentagens[J,B]
                    B       -2682.22                          -0 
     7 maxPercentagens[J,C]
                    B              0                          -0 
     8 maxPercentagens[O,A]
                    B       -1526.67                          -0 
     9 maxPercentagens[O,B]
                    B       -1673.33                          -0 
    10 maxPercentagens[O,C]
                    B              0                          -0 
    11 maxPercentagens[M,A]
                    B       -508.889                          -0 
    12 maxPercentagens[M,B]
                    B       -693.333                          -0 
    13 maxPercentagens[M,C]
                    B              0                          -0 
    14 minPercentagens[J,A]
                    NL             0            -0                    -24.4444 
    15 minPercentagens[J,B]
                    NL             0            -0                    -24.4444 
    16 minPercentagens[J,C]
                    B              0            -0               
    17 minPercentagens[O,A]
                    B        1017.78            -0               
    18 minPercentagens[O,B]
                    B        1482.22            -0               
    19 minPercentagens[O,C]
                    B              0            -0               
    20 minPercentagens[M,A]
                    B              0            -0               
    21 minPercentagens[M,B]
                    B           1200            -0               
    22 minPercentagens[M,C]
                    B              0            -0               
    23 totalMarca[J]
                    NS             0            -0             =      -77.7778 
    24 totalMarca[O]
                    NS             0            -0             =      -53.3333 
    25 totalMarca[M]
                    NS             0            -0             =      -53.3333 
    26 totalMistura[A]
                    NS             0            -0             =       53.3333 
    27 totalMistura[B]
                    NS             0            -0             =       53.3333 
    28 totalMistura[C]
                    NS             0            -0             =       53.3333 

   No. Column name  St   Activity     Lower bound   Upper bound    Marginal
------ ------------ -- ------------- ------------- ------------- -------------
     1 numMistura[A]
                    B        2544.44             0               
     2 numMistura[B]
                    B        3155.56             0               
     3 numMistura[C]
                    NL             0             0                    -8.33333 
     4 numMarca[J]  B           2000             0               
     5 numMarca[O]  B           2500             0               
     6 numMarca[M]  B           1200             0               
     7 numGarrafas[J,A]
                    B        1526.67             0               
     8 numGarrafas[J,B]
                    B        473.333             0               
     9 numGarrafas[J,C]
                    NL             0             0                    -24.4444 
    10 numGarrafas[O,A]
                    B        1017.78             0               
    11 numGarrafas[O,B]
                    B        1482.22             0               
    12 numGarrafas[O,C]
                    B              0             0               
    13 numGarrafas[M,A]
                    NL             0             0                       < eps
    14 numGarrafas[M,B]
                    B           1200             0               
    15 numGarrafas[M,C]
                    NL             0             0                       < eps

Karush-Kuhn-Tucker optimality conditions:

KKT.PE: max.abs.err = 2.27e-13 on row 14
        max.rel.err = 7.44e-17 on row 14
        High quality

KKT.PB: max.abs.err = 0.00e+00 on row 0
        max.rel.err = 0.00e+00 on row 0
        High quality

KKT.DE: max.abs.err = 1.42e-14 on column 7
        max.rel.err = 9.08e-17 on column 7
        High quality

KKT.DB: max.abs.err = 0.00e+00 on row 0
        max.rel.err = 0.00e+00 on row 0
        High quality

End of output
