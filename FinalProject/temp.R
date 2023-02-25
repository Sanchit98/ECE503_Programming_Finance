library(ggplot2)
p <- ggplot(data = stock_portfolio, mapping = aes(x = V2, y = V1, group = 1)) + 
  geom_line(color = "#1d3557", linewidth = 2)
print(p)