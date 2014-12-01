library(ggplot2)
multiplot <- function(..., plotlist=NULL, file, cols=1, layout=NULL) {
  require(grid)
  # Make a list from the ... arguments and plotlist
  plots <- c(list(...), plotlist)
  numPlots = length(plots)
  # If layout is NULL, then use 'cols' to determine layout
  if (is.null(layout)) {
    # Make the panel
    # ncol: Number of columns of plots
    # nrow: Number of rows needed, calculated from # of cols
    layout <- matrix(seq(1, cols * ceiling(numPlots/cols)),
                    ncol = cols, nrow = ceiling(numPlots/cols))
  }
 if (numPlots==1) {
    print(plots[[1]])
  } else {
    # Set up the page
    grid.newpage()
    pushViewport(viewport(layout = grid.layout(nrow(layout), ncol(layout))))
    # Make each plot, in the correct location
    for (i in 1:numPlots) {
      # Get the i,j matrix positions of the regions that contain this subplot
      matchidx <- as.data.frame(which(layout == i, arr.ind = TRUE))
      print(plots[[i]], vp = viewport(layout.pos.row = matchidx$row, layout.pos.col = matchidx$col))
    }
  }
}

x_2 <- c(0,2,1,3,2,3,3,5,4,2,4,6,9,12,11,9,15,10,14,16,19,17,14,21,20,20,28,29,33)
x <- c(x_2[3:29],c(31,35))-1
y <- c(2,3,4,3,3,4,6,7,8,5,13,16,14,15,15,17,19,19,19,20,20,18,20,17,22,25,29,30,33)
y_2 <- c(x[3:29],c(30,29))+1
dat <- as.data.frame(cbind(x,x_2,y,y_2))
p1 <- ggplot(dat, aes(x = x, y = y))
p2 <- p1 + geom_point(color = "blue") + geom_line() + ggtitle("Title goes here")
p3 <- ggplot(dat, aes(x = x_2, y = y_2))
p4 <- p3 + geom_point(color = "red") + geom_line() + ggtitle("Title goes here")
p2
p4
multiplot(p2,p4)

library(ggplot2)
y <- c(2,3,4,3,3,4,6,7,8,5,13,16,14,15,15,17,19,19,19,20,20,18,20,17,22,25,29,30,33)
y_2 <- c(y[3:29],c(30,29))+1
x <- 1:29
x_2 <- 1:29
dat <- data.frame(Time = x, DemandForecast = y, Group = rep("DualBalancing", 29))
dat_2 <- data.frame(Time = x_2, DemandForecast = y_2, Group = rep("DynamicProgramming", 29))
dat <- rbind(dat,dat_2)

ggplot(dat, aes(x=Time, y=DemandForecast, group=Group, colour=Group)) + geom_point() + geom_line() + ggtitle("Stochastic Lead Time Algorithm Performance") + coord_fixed(ratio=1/3)