#limpar workspace
rm(list=ls())

#limpar tela
cat('\014')

#bibliotecas
library("RSNNS")
library("vioplot")

#---------------------------------------
#FUNCOES
#funcao que ajusta outliers de qualquer amostra
ajustaOutliers <- function(x, na.rm = TRUE, ...) 
{
  qnt <- quantile(x, probs=c(.25, .75), na.rm = na.rm, ...)
  H <- 1.5 * IQR(x, na.rm = na.rm)
  y <- x
  y[x < (qnt[1] - H)] <- NA
  y[x > (qnt[2] + H)] <- NA
  
  for(i in 1:length(y)) 
  {
    #caso o primeiro valor seja NA procura o proximo valor nao NA e coloca
    #no lugar do NA
    if (is.na(y[1]) == TRUE)
    {
      encontrou = FALSE
      cont = 1
      posterior = NA
      #procura o primeiro numero POSTERIOR ao valor atual que nao seja NA
      while (encontrou == FALSE)
      {
        if (is.na(y[1+cont]) == TRUE)
        {
          cont <- cont + 1
        }
        else
        {
          posterior <- y[1+cont];
          encontrou <- TRUE
        }
      }
      
      y[1] <- posterior
    }
    
    #caso o ultimo valor seja NA procura o primeiro valor anterior que nao NA e coloca
    #no lugar do NA
    if (is.na(y[length(y)]) == TRUE)
    {
      encontrou <- FALSE
      cont <- 1
      anterior <- NA
      
      #procura o primeiro numero ANTERIOR ao valor atual que nao seja NA
      while (encontrou == FALSE)
      {
        if (is.na(y[length(y)-cont]) == TRUE)
        {
          cont <- cont + 1
        }
        else
        {
          anterior <- y[length(y)-cont];
          encontrou <- TRUE
        }
      }
      
      y[length(y)] <- anterior
    }
    
    
    
    if (is.na(y[i])==TRUE)
    {
      encontrou <- FALSE
      cont <- 1
      anterior <- NA
      
      #procura o primeiro numero ANTERIOR ao valor atual que nao seja NA
      while (encontrou == FALSE)
      {
        if (is.na(y[i-cont]) == TRUE)
        {
          cont <- cont + 1
        }
        else
        {
          anterior <- y[i-cont];
          encontrou <- TRUE
        }
      }
      
      encontrou = FALSE
      cont = 1
      posterior = NA
      
      #procura o primeiro numero POSTERIOR ao valor atual que nao seja NA
      while (encontrou == FALSE)
      {
        if (is.na(y[i+cont]) == TRUE)
        {
          cont <- cont + 1
        }
        else
        {
          posterior <- y[i+cont];
          encontrou <- TRUE
        }
      }
      
      #executa uma media entre o anterior e posterior valor valido na serie e insere no lugar do outlier
      y[i] <- (anterior+posterior)/2
    }
  }
  
  return(y)
}

#Coloca amostra nos intervalos proporcionais entre 0 e 1
padroniza <- function(s)
{
  retorno <- (s - min(s))/(max(s)-min(s))
  return(retorno)
}

carrega_subset <- function(arquivo) 
{
  dados <- read.table(arquivo,
                      header=TRUE,
                      sep=";",
                      colClasses=c("numeric", "character", "character", rep("numeric",2)),
                      na="?")
  
  return(dados)
}

#Voltar escala de temperatura
despadronizatemp <- function(s, maxv, minv)
{
  
  s*(maxv - minv) + minv 
}

#---------------------------------------

#Carregando dataset
temperatura <- carrega_subset("temp.txt")
temperatura <- temperatura[,-c(1,3,6)]

#Separando dataset por ano
dados2015 <- temperatura[1:365,]
dados2016 <- temperatura[366:731,]

#TRATAMENTO DE DADOS
umidadeComOut <- dados2015$Umidade.Relativa.Media
umidadeSemOut <- ajustaOutliers(dados2015$Umidade.Relativa.Media)

#ANALISE DA DISPERSAO DOS DADOS
dadosUmidade <- cbind(umidadeComOut,umidadeSemOut)
colnames(dadosUmidade) <- c("Com Outliers", "Sem Outliers")
vioplot(dadosUmidade[,2], dadosUmidade[,1], names=c("Sem Outliers","Com Outliers"), col=c("cyan"), horizontal=TRUE, lty=2, rectCol="gray", pchMed=19)
title("Comparativo da dispersão das umidades com e sem outliers ao longo do ano de 2015", cex.main=0.8) 

#ANALISE DA EVOLUCAO DA UMIDADE AO LONGO DO ANO
plot(umidadeComOut, main="Umidade diária ao longo de 2015", xlab="Dias", ylab="Umidade", cex.lab=0.8, cex.axis=0.8, cex.main=0.8, cex.sub=0.8, col="red", type="p", ylim=c(40,110))
par(new=T)
plot(umidadeSemOut, main="", xlab="", ylab="", cex.lab=0.8, cex.axis=0.8, cex.main=0.8, cex.sub=0.8, col="blue",type="l", ylim=c(40,110))
abline(v=79, col="red", lty=2) #outono
abline(v=172, col="red", lty=2) #inverno
abline(v=265, col="red", lty=2) #primavera
abline(v=355, col="red", lty=2) #verao

legend("bottom",col=c("blue", "red"), c("Sem out", "Com out"),lty=1, cex = 0.8, pt.cex = 1)
text(35, 108,"Verão", col="orange")
text(130, 108,"Outono", col="orange")
text(220, 108,"Inverno", col="orange")
text(310, 108,"Primavera", col="orange")

#OBSERVANDO OS DADOS DE TEMPERATURA
TempComOut <- dados2015$TempMaxima
TempSemOut <- ajustaOutliers(dados2015$TempMaxima)

#ANALISE DA DISPERSAO DOS DADOS
dadosTemp <- cbind(TempComOut,TempSemOut)
colnames(dadosTemp) <- c("Com Outliers", "Sem Outliers")
vioplot(dadosTemp[,1], dadosTemp[,2], names=c("Sem Outliers","Com Outliers"), col=c("cyan"), horizontal=TRUE, lty=2, rectCol="gray", pchMed=19)
title("Comparativo da dispersão das temperatura com e sem outliers ao longo do ano de 2015", cex.main=0.8) 

#ANALISE DA EVOLUCAO DA UMIDADE AO LONGO DO ANO
plot(TempComOut, main="Temperatura diária ao longo de 2015", xlab="Dias", ylab="Temperatura", cex.lab=0.8, cex.axis=0.8, cex.main=0.8, cex.sub=0.8, col="red", type="p", ylim=c(15,45))
par(new=T)
plot(TempSemOut, main="", xlab="", ylab="", cex.lab=0.8, cex.axis=0.8, cex.main=0.8, cex.sub=0.8, col="blue",type="l", ylim=c(15,45))
abline(v=79, col="red", lty=2) #outono
abline(v=172, col="red", lty=2) #inverno
abline(v=265, col="red", lty=2) #primavera
abline(v=355, col="red", lty=2) #verao

legend("bottom",col=c("blue", "red"), c("Sem out", "Com out"),lty=1, cex = 0.6, pt.cex = 1)
text(35, 43,"Verão", col="orange")
text(130, 43,"Outono", col="orange")
text(220, 43,"Inverno", col="orange")
text(310, 43,"Primavera", col="orange")

#IMPLEMENTACAO DA REDE NEURAL NOS DADOS AJUSTADOS
x1 <- padroniza(seq(1:length(dados2015$Data)))
x2 <- padroniza(umidadeSemOut)
x <- cbind(x1,x2) #data / umidade sem outliers padronizada entre 0 e 1
colnames(x) <- c("data","umidade")

y <- padroniza(TempSemOut)
rm(x1,x2)

#TREINAMENTO DA REDE NEURAL
set.seed(1)

#configuracoes da RNA
nNeuronios = 38
maxEpocas <- 15000

#treinamento da MLP
redeMLP <- NULL
redeRBF <- NULL
redeEL <- NULL
redeJO <- NULL

print("--- Treinamento das Redes ---")
#---------------------------------------
#---------------MLP---------------------
load('redeMLP.Rdata')
print("--- Treinando MLP ---")
#redeMLP<-mlp(x, y, size=nNeuronios, maxit=maxEpocas, initFunc="Randomize_Weights",
#            initFuncParams=c(-0.3, 0.3), learnFunc="Std_Backpropagation",
#            learnFuncParams=c(0.0008), updateFunc="Topological_Order",
#            updateFuncParams=c(0), hiddenActFunc="Act_Logistic",
#            shufflePatterns=TRUE, linOut=FALSE)

plot(redeMLP$IterativeFitError,type="l",main="Convergência do erro da MLP", xlab="Epocas", ylab="Erro")
#print(redeMLP$IterativeFitError[length(redeMLP$IterativeFitError)])

#save(redeMLP, file="redeMLP.Rdata")

#EXECUTANDO A PREVISOES COM O MODELO TREINADO
yhat = vector()
for (i in 1:dim(x)[1])
{
  yhat[i] = predict(redeMLP,x[i,])
}

yd <- despadronizatemp(y, max(dados2015$TempMaxima),min(dados2015$TempMaxima))
yhat <- despadronizatemp(yhat, max(dados2015$TempMaxima),min(dados2015$TempMaxima))

#plot da aproximacao da funcao no conjunto de treinamento
plot(yd,type="l",col="blue",xlab="",ylab="")
par(new=T)
plot(yhat,col="red",type="l",xaxt='n',yaxt='n', main="Previsão MLP 2015", xlab="Dias", ylab="Temperatura")

legend("top",col=c("blue", "red"), c("Temp Real", "Temp Prevista"),lty=1, cex = 0.6, pt.cex = 1)

#---------------RBF---------------------
load('redeRBF.Rdata')
print("--- Treinando RBF ---")
#redeRBF<-rbf(x, y, size=nNeuronios, maxit=maxEpocas, initFunc="RBF_Weights",
#            initFuncParams=c(0, 1, 0, 0.02, 0.04), learnFunc="RadialBasisLearning",
#            learnFuncParams=c(1e-05, 0, 1e-05, 0.1, 0.8), updateFunc="Topological_Order",
#            updateFuncParams=c(0), hiddenActFunc="Act_Logistic",
#            shufflePatterns=TRUE, linOut=FALSE)

plot(redeRBF$IterativeFitError,type="l",main="Convergência do erro da RBF", xlab="Epocas", ylab="Erro")

#EXECUTANDO A PREVISOES COM O MODELO TREINADO
yrbf = vector()
for (i in 1:365)
{
  yrbf[i] = predict(redeRBF,x[i,])
}

yrbf <- despadronizatemp(yrbf, max(dados2015$TempMaxima),min(dados2015$TempMaxima))

#plot da aproximacao da funcao
plot(yd,type="l",col="blue",xlab="",ylab="")
par(new=T)
plot(yrbf,col="red",type="l",xaxt='n',yaxt='n',main="Previsão RBF 2015", xlab="Dias", ylab="Temperatura")
legend("top",col=c("blue", "red"), c("Temp Real", "Temp Prevista"),lty=1, cex = 0.6, pt.cex = 1)

#---------------ELMAN------------------------
load('redeEL.Rdata')
print("--- Treinando ELMAN ---")
#redeEL<-elman(x, y, size=nNeuronios, maxit=maxEpocas, initFunc="JE_Weights",
#             initFuncParams=c(1, -1, 0.3, 1, 0.5), learnFunc="JE_BP",
#             learnFuncParams=c(0.0008), updateFunc="JE_Order",
#             updateFuncParams=c(0), hiddenActFunc="Act_Logistic",
#            shufflePatterns=TRUE, linOut=FALSE, outContext = TRUE)

plot(redeEL$IterativeFitError,type="l",main="Convergência do erro da ELMAN", xlab="Epocas", ylab="Erro")
#EXECUTANDO A PREVISOES COM O MODELO TREINADO
yel = vector()
for (i in 1:365)
{
  yel[i] = predict(redeEL,x[i,])
}

yel <- despadronizatemp(yel, max(dados2015$TempMaxima),min(dados2015$TempMaxima))

#plot da aproximacao da funcao
plot(yd,type="l",col="blue",xlab="",ylab="")
par(new=T)
plot(yel,col="red",type="l",xaxt='n',yaxt='n', main="Previsão ELMAN 2015", xlab="Dias", ylab="Temperatura")
legend("top",col=c("blue", "red"), c("Temp Real", "Temp Prevista"),lty=1, cex = 0.6, pt.cex = 1)

#---------------JORDAN------------------------
load('redeJO.Rdata')
print("--- Treinando JORDAN ---")
#redeJO<-jordan(x, y, size=nNeuronios, maxit=maxEpocas, initFunc="JE_Weights",
#            initFuncParams=c(1, -1, 0.3, 1, 0.5), learnFunc="JE_BP",
#            learnFuncParams=c(0.0008), updateFunc="JE_Order",
#            updateFuncParams=c(0), hiddenActFunc="Act_Logistic",
#            shufflePatterns=TRUE, linOut=FALSE, outContext = TRUE)

plot(redeJO$IterativeFitError,type="l", xlab="Epocas", ylab="Erro", main="Convergência do erro da JORDAN")

#EXECUTANDO A PREVISOES COM O MODELO TREINADO
yjo = vector()
for (i in 1:365)
{
  yjo[i] = predict(redeJO,x[i,])
}

yjo <- despadronizatemp(yjo, max(dados2015$TempMaxima),min(dados2015$TempMaxima))

#plot da aproximacao da funcao
plot(yd,type="l",col="blue",xlab="",ylab="")
par(new=T)
plot(yjo,col="red",type="l",xaxt='n',yaxt='n', main="Previsão JORDAN 2015", xlab="Dias", ylab="Temperatura")
legend("top",col=c("blue", "red"), c("Temp Real", "Temp Prevista"),lty=1, cex = 0.6, pt.cex = 1)

#---------------------------------------
print("--- Redes Treinadas ---")

#Prevendo temperatura de 2016
x4 <- padroniza(seq(1:length(dados2016$Data)))
x5 <- padroniza(dados2016$Umidade.Relativa.Media)
x6 <- cbind(x4,x5)
y2 <- padroniza(dados2016$TempMaxima)

colnames(x6)<-c("Data","Umidade")

#Preencher Umidade da tabela x6
x6[1,2] <- x[365,2]

for(i in 2:366){
  x6[i,2]<-x5[i-1]
}

print("--- Previsão ---")
#Executando as previsões de 2016
#--------------PREVISÃO MLP--------------------------
print("--- Prevendo com MLP ---")
yhat2<-vector()
yhat2[1]<- predict(redeMLP,x6[1,])
for(i in 2:366){
  yhat2[i] <- predict(redeMLP,x6[i-1,])
}

y2 <- despadronizatemp(y2, max(dados2015$TempMaxima),min(dados2015$TempMaxima))
yhat2 <- despadronizatemp(yhat2, max(dados2015$TempMaxima),min(dados2015$TempMaxima))

plot(y2,type="l",col="blue",xlab="",ylab="")
par(new=T)
plot(yhat2,col="red",type="l",xlab="",ylab="",xaxt='n',yaxt='n', main="Previsão 2016 com MLP")
par(new=T)
plot(lowess(yhat2, f = .2), col="green",type="l",xlab="",ylab="",xaxt='n',yaxt='n', main="Previsão 2016 com MLP")
legend("top",col=c("blue", "red", "green"), c("Temp Real", "Temp Prevista", "Lowess"),lty=1, cex = 0.5)

#--------------Previsão RBF--------------------------
print("--- Prevendo com RBF ---")
yrbf2<-vector()
yrbf2[1]<- predict(redeRBF,x6[1,])
for(i in 2:366){
  yrbf2[i] <- predict(redeRBF,x6[i-1,])
}

yrbf2 <- despadronizatemp(yrbf2, max(dados2015$TempMaxima),min(dados2015$TempMaxima))

plot(y2,type="l",col="blue",xlab="",ylab="")
par(new=T)
plot(yrbf2,col="red",type="l",xlab="",ylab="",xaxt='n',yaxt='n', main="Previsão 2016 com RBF")
par(new=T)
plot(lowess(yrbf2, f = .2), col="green",type="l",xlab="Dias",ylab="Temperatura",xaxt='n',yaxt='n')
legend("top",col=c("blue", "red", "green"), c("Temp Real", "Temp Prevista", "Lowess"),lty=1, cex = 0.5)

#--------------PREVISÃO ELMAN------------------------
print("--- Prevendo com ELMAN ---")
yel2<-vector()
yel2[1]<- predict(redeEL,x6[1,])
for(i in 2:366){
  yel2[i] <- predict(redeEL,x6[i-1,])
}

yel2 <- despadronizatemp(yel2, max(dados2015$TempMaxima),min(dados2015$TempMaxima))

plot(y2,type="l",col="blue",xlab="",ylab="")
par(new=T)
plot(yel2,col="red",type="l",xlab="",ylab="",xaxt='n',yaxt='n', main="Previsão 2016 com ELMAN")
par(new=T)
plot(lowess(yel2, f = .2), col="green",type="l",xlab="Dias",ylab="Temperatura",xaxt='n',yaxt='n')
legend("top",col=c("blue", "red", "green"), c("Temp Real", "Temp Prevista", "Lowess"),lty=1, cex = 0.5)

#--------------PREVISÃO JORDAN-----------------------
print("--- Prevendo com JORDAN ---")
yjo2<-vector()
yjo2[1]<- predict(redeJO,x6[1,])
for(i in 2:366){
  yjo2[i] <- predict(redeJO,x6[i-1,])
}

yjo2 <- despadronizatemp(yjo2, max(dados2015$TempMaxima),min(dados2015$TempMaxima))

plot(y2,type="l",col="blue",xlab="",ylab="")
par(new=T)
plot(yjo2,col="red",type="l",xlab="",ylab="",xaxt='n',yaxt='n', main="Previsão 2016 com JORDAN")
par(new=T)
plot(lowess(yjo2, f = .2), col="green",type="l",xlab="Dias",ylab="Temperatura",xaxt='n',yaxt='n')
legend("top",col=c("blue", "red", "green"), c("Temp Real", "Temp Prevista", "Lowess"),lty=1, cex = 0.5)

#----------------------------------------------------

#Erros da Previsão de 2016
erro2016mlp <- mean(sqrt((y2-yhat2)^2))
erro2016rbf <- mean(sqrt((y2-yrbf2)^2))
erro2016elman <- mean(sqrt((y2-yel2)^2))
erro2016jordan <- mean(sqrt((y2-yjo2)^2))

print(paste("ERRO da Previsão de 2016 da MLP:",erro2016mlp))
print(paste("ERRO da Previsão de 2016 da RBF:",erro2016rbf))
print(paste("ERRO da Previsão de 2016 da ELMAN :",erro2016elman))
print(paste("ERRO da Previsão de 2016 da JORDAN:",erro2016jordan))
