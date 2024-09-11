library(bayeos)

# TODO:Please adapt the connection information
bayeos.connect("https://bayeos.bayceer.uni-bayreuth.de/BayEOS-Server/XMLServlet",
<<<<<<<< HEAD:15_BayEOS Server Access/BayEOS R/bayconf.R
    user = "workshop", password = "CHANGE_ME", save_as = "workshop"
========
    user = "workshop", password = "CHANGE ME!", save_as = "workshop"
>>>>>>>> 0045ac507cbc679d505b0da95f82fb885ab1bf0f:15_BayEOS Server Access/R/bayconf.R
)

bayeos.connect("workshop")
bayeos.ls()
bayeos.cd(138398)

d <- bayeos.getSeries(c(138399, 138400))
plot(d)
