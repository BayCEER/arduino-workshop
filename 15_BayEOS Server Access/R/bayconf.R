library(bayeos)

# TODO:Please adapt the connection information
bayeos.connect("https://bayeos.bayceer.uni-bayreuth.de/BayEOS-Server/XMLServlet",
    user = "workshop", password = "CHANGE ME!", save_as = "workshop"
)

bayeos.connect("workshop")
bayeos.ls()
bayeos.cd(138398)

d <- bayeos.getSeries(c(138399, 138400))
plot(d)
