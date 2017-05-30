mcts1 <- read.csv("MCTSk1.txt", header = FALSE, sep = " ")
mcts01 <- read.csv("MCTSk01.txt", header = FALSE, sep = " ")
mcts03 <- read.csv("MCTSk03.txt", header = FALSE, sep = " ")
mcts08 <- read.csv("MCTSk08.txt", header = FALSE, sep = " ")



trial <- matrix(c(mcts01$V2,mcts03$V2,mcts08$V2,mcts1$V2), ncol=4)

boxplot(trial, names=c("0.1", "0.3", "0.8", "1"), main="Monte Carlo Tree Search en fonction de K",xlab="Valeur de K", ylab="Score")

hist(mcts1$V2, main = "MCTS avec k = 1", xlab = "Score", ylab = "Fréquence")
hist(mcts01$V2, main = "MCTS avec k = 0.1", xlab = "Score", ylab = "Fréquence")
hist(mcts03$V2, main = "MCTS avec k = 0.3", xlab = "Score", ylab = "Fréquence")
hist(mcts08$V2, main = "MCTS avec k = 0.8", xlab = "Score", ylab = "Fréquence")


plot(mcts01, type="l", col="blue", xlim=c(0,50))
lines(mcts03, col="darkgreen")
lines(mcts08, col="red")
lines(mcts1, col="brown")

legend(0, 25, legend=c("K = 0.1", "K = 0.3", "K = 0.8", "K = 1"), col=c("blue", "darkgreen", "red", "brown"), lty=1)
