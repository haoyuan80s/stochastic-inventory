library(ggplot2)

db_output01 <- read.csv("output/db_output01.csv")
db_output02 <- read.csv("output/db_output02.csv")
db_output03 <- read.csv("output/db_output03.csv")
db_output04 <- read.csv("output/db_output04.csv")

my_output01 <- read.csv("output/my_output01.csv")
my_output02 <- read.csv("output/my_output02.csv")
my_output03 <- read.csv("output/my_output03.csv")
my_output04 <- read.csv("output/my_output04.csv")

myopic_bad_case <- read.csv("output/myopic_bad_case.csv")

tc_to <- read.csv("output/tc_to.csv")
tc_to_y <- (tc_to$TotalCostN/tc_to$TotalOrderingN)
tc_to_y_2 <- (tc_to$TotalCostIN/tc_to$TotalOrderingIN)
tc_to_x <- (0:20)*20

net_inv_1 <- read.csv("output/net_inv_1.csv")
net_inv_2 <- read.csv("output/net_inv_2.csv")
net_inv_1$NetInventory0
net_inv_1$NetInventory20
net_inv_1$NetInventory40
net_inv_1$NetInventory60
net_inv_2$NetInventory0
net_inv_2$NetInventory20
net_inv_2$NetInventory40
net_inv_2$NetInventory60

#dp_output01 <- read.csv("output/dp_output01.csv")
#dp_output02 <- read.csv("output/dp_output02.csv")
#dp_output03 <- read.csv("output/dp_output03.csv")
#dp_output04 <- read.csv("output/dp_output04.csv")

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

g_legend<-function(a.gplot){
  tmp <- ggplot_gtable(ggplot_build(a.gplot))
  leg <- which(sapply(tmp$grobs, function(x) x$name) == "guide-box")
  legend <- tmp$grobs[[leg]]
  return(legend)}

plot_2_graph <- function(y,y_title,y2,y2_title,y_axs_title,nrows,title) {
  line_1 <- data.frame(TimePeriod = 0:nrows, DemandAndCost = y, Group = rep(y_title, nrows+1))
  line_2 <- data.frame(TimePeriod = 0:nrows, DemandAndCost = y2, Group = rep(y2_title, nrows+1))
  dat <- rbind(line_1,line_2)
  ggplot(dat, aes(x=TimePeriod, y=DemandAndCost, group=Group, colour=Group)) + ggtitle(title) + theme(axis.text=element_text(size=6),axis.title=element_text(size=6), title=element_text(size=8),legend.position='bottom',legend.title = element_text(color="#ffffff",size=10),legend.text = element_text(size=6))
}

plot_graph <- function(y,y_title,y2,y2_title,y3,y3_title,y4,y4_title,y_axs_title,nrows,title) {
  line_1 <- data.frame(TimePeriod = 0:nrows, DemandAndCost = y, Group = rep(y_title, nrows+1))
  line_2 <- data.frame(TimePeriod = 0:nrows, DemandAndCost = y2, Group = rep(y2_title, nrows+1))
  line_3 <- data.frame(TimePeriod = 0:nrows, DemandAndCost = y3, Group = rep(y3_title, nrows+1))
  line_4 <- data.frame(TimePeriod = 0:nrows, DemandAndCost = y4, Group = rep(y4_title, nrows+1))
  dat <- rbind(line_1,line_2,line_3,line_4)
  ggplot(dat, aes(x=TimePeriod, y=DemandAndCost, group=Group, colour=Group)) + geom_point(size=1.5,alpha=.7) + ggtitle(title) + theme(legend.position = "none", axis.text=element_text(size=6),axis.title=element_text(size=10), title=element_text(size=9))
}

#Independent Normal
AccumulativeDemandAndCost_Normal <- plot_graph(db_output01$AccumulativeDemand, "DualBalancingAccumulativeDemand", db_output01$AccumulativeCost,"DualBalancingAccumulativeCost",my_output01$AccumulativeDemand,"MyopicAccumulativeDemand",my_output01$AccumulativeCost,"MyopicAccumulativeCost","AccumulativeDemandAndCost",100,"Accumulative Demand vs. Accumulative Cost:\n Independent Normal")
#Binomial Increment
AccumulativeDemandAndCost_Binomial <- plot_graph(db_output02$AccumulativeDemand, "DualBalancingAccumulativeDemand", db_output02$AccumulativeCost,"DualBalancingAccumulativeCost",my_output02$AccumulativeDemand,"MyopicAccumulativeDemand",my_output02$AccumulativeCost,"MyopicAccumulativeCost","AccumulativeDemandAndCost",100,"Accumulative Demand vs. Accumulative Cost:\n Binomial Increment")
#Brownian Motion with Drift
AccumulativeDemandAndCost_Brownian <- plot_graph(db_output03$AccumulativeDemand, "DualBalancingAccumulativeDemand", db_output03$AccumulativeCost,"DualBalancingAccumulativeCost",my_output03$AccumulativeDemand,"MyopicAccumulativeDemand",my_output03$AccumulativeCost,"MyopicAccumulativeCost","AccumulativeDemandAndCost",100,"Accumulative Demand vs. Accumulative Cost:\n Brownian Motion with Drift")
#3-period Markov Chain
AccumulativeDemandAndCost_Markov <- plot_graph(db_output04$AccumulativeDemand, "DualBalancingAccumulativeDemand", db_output04$AccumulativeCost,"DualBalancingAccumulativeCost",my_output04$AccumulativeDemand,"MyopicAccumulativeDemand",my_output04$AccumulativeCost,"MyopicAccumulativeCost","AccumulativeDemandAndCost",100,"Accumulative Demand vs. Accumulative Cost:\n 3-period Markov Chain")

#Independent Normal
DemandAndNetInventory_Normal <- plot_graph(db_output01$Demand, "DualBalancingDemand", db_output01$NetInventory,"DualBalancingNetInventory",my_output01$Demand,"MyopicDemand",my_output01$NetInventory,"MyopicNetInventory","DemandAndNetInventory",100,"Demand vs. Net Inventory:\n Independent Normal")
#Binomial Increment
DemandAndNetInventory_Binomial <- plot_graph(db_output02$Demand, "DualBalancingDemand", db_output02$NetInventory,"DualBalancingNetInventory",my_output02$Demand,"MyopicDemand",my_output02$NetInventory,"MyopicNetInventory","DemandAndNetInventory",100,"Demand vs. Net Inventory:\n Binomial Increment")
#Brownian Motion with Drift
DemandAndNetInventory_Brownian <- plot_graph(db_output03$Demand, "DualBalancingDemand", db_output03$NetInventory,"DualBalancingNetInventory",my_output03$Demand,"MyopicDemand",my_output03$NetInventory,"MyopicNetInventory","DemandAndNetInventory",100,"Demand vs. Net Inventory:\n Brownian Motion with Drift")
#3-period Markov Chain
DemandAndNetInventory_Markov <- plot_graph(db_output04$Demand, "DualBalancingDemand", db_output04$NetInventory,"DualBalancingNetInventory",my_output04$Demand,"MyopicDemand",my_output04$NetInventory,"MyopicNetInventory","DemandAndNetInventory",100,"Demand vs. Net Inventory:\n 3-period Markov Chain")

#Myopic Bad: Demand
MyopicBadDemand <- plot_2_graph(myopic_bad_case$DemandMY, "MyopicDemand", myopic_bad_case$DemandDB,"DualBalancingDemand","blah",200,"Myopic Bad Case: Comparing Demand") + geom_point()
#Myopic Bad: Net Inventory
MyopicBadNetInventory <- plot_2_graph(myopic_bad_case$NetInventoryMY, "MyopicNetInventory", myopic_bad_case$NetInventoryDB,"DualBalancingNetInventory","blah",200,"Myopic Bad Case: Comparing Net Inventory") + geom_line()
#Myopic Bad: Cumulative Cost
MyopicBadAccumulativeCost <- plot_2_graph(myopic_bad_case$AccumulativeCostMY, "MyopicAccumulativeCost", myopic_bad_case$AccumulativeCostDB,"DualBalancingAccumulativeCost","blah",200,"Myopic Bad Case: Comparing Accumulative Cost") + geom_line()
#Myopic Bad: Ordering
MyopicBadOrdering <- plot_2_graph(myopic_bad_case$OrderingMY, "MyopicOrdering", myopic_bad_case$OrderingDB,"DualBalancingOrdering","blah",200,"Myopic Bad Case: Comparing Ordering")+xlim(0,30) + geom_line()

ggsave(MyopicBadDemand,file="MyopicBadDemand.png", scale=.5)
ggsave(MyopicBadNetInventory,file="MyopicBadNetInventory.png", scale=.5)
ggsave(MyopicBadAccumulativeCost,file="MyopicBadAccumulativeCost.png", scale=.5)
ggsave(MyopicBadOrdering,file="MyopicBadOrdering.png", scale=.5)

#ggsave(AccumulativeDemandAndCost_Normal,file="AccumulativeDemandAndCost_Normal.png", scale=.5)
#ggsave(AccumulativeDemandAndCost_Binomial,file="AccumulativeDemandAndCost_Binomial.png", scale=.5)
#ggsave(AccumulativeDemandAndCost_Brownian,file="AccumulativeDemandAndCost_Brownian.png", scale=.5)
#ggsave(AccumulativeDemandAndCost_Markov,file="AccumulativeDemandAndCost_Markov.png", scale=.5)

#ggsave(DemandAndNetInventory_Normal,file="DemandAndNetInventory_Normal.png", scale=.5)
#ggsave(DemandAndNetInventory_Binomial,file="DemandAndNetInventory_Binomial.png", scale=.5)
#ggsave(DemandAndNetInventory_Brownian,file="DemandAndNetInventory_Brownian.png", scale=.5)
#ggsave(DemandAndNetInventory_Markov,file="DemandAndNetInventory_Markov.png", scale=.5)

multiplot(p1,p2,p3,p4,cols=2)
#multiplot(q1,q2,q3,q4,cols=2)