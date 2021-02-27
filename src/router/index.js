import Vue from 'vue';
import Router from 'vue-router';
Vue.use(Router);

export function createRouter(ssrContext, createDefaultRouter, routerOptions) {
  const options = routerOptions || createDefaultRouter(ssrContext).options;

  //const hostname = ssrContext ? ssrContext.req.headers.host : location.host;
  //To access hostname from firebase use x-forwarded-host
  const domain = ssrContext ? ssrContext.req.headers['x-forwarded-host'] : location.host;

  //let group = /^([\w\.]+)(:\d+)?$/.exec(hostname);

  //let domain = group ? group[1] : "";

  //domain = domain.toLowerCase();

  //let domain = hostname.match(/[-\w+\.]+/);

  return new Router({
    ...options,
    routes: formatRoutes(options.routes, domain),
  });
}

function formatRoutes(defaultRoutes, domain) {
  let routes = [];
  defaultRoutes.forEach(route => {
    //if (!RegExp(`^\/${domain.replace(/\./, '\\.')}($|\\/.*)`).test(route.path))
    if (RegExp(`${domain}`).test(route.path)) {
      //route.path = route.path.replace(new RegExp(`^\\/${domain}\\/?`), "/");
      routes.push({
        path: route.path.replace(new RegExp(`/${domain}/?`), "/"),
        component: route.component,
        name: route.name,
      });
    }
  });

  console.log(defaultRoutes);
  console.log(domain);
  console.log(routes);

  return routes;
}
