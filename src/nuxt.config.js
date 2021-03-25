module.exports =  {
  // Global page headers: https://go.nuxtjs.dev/config-head
  head: {
    title: 'RZK Market 2.0',
    htmlAttrs: {
      lang: 'ru'
    },
    meta: [
      { charset: 'utf-8' },
      { name: 'viewport', content: 'width=device-width, initial-scale=1' },
      { hid: 'description', name: 'description', content: 'RZK Market маркетплейс' },
      {
        hid: 'keywords',
        name: 'keywords',
        content: 'купить товары, rzk маркет, rzk market'
      }
    ],
    link: [
      { hid: 'icon', rel: 'icon', type: 'image/x-icon', href: '/favicon.ico' }
    ]
  },

  // Global CSS: https://go.nuxtjs.dev/config-css
  css: [
  ],

  // Plugins to run before rendering page: https://go.nuxtjs.dev/config-plugins
  plugins: [
  ],

  // Auto import components: https://go.nuxtjs.dev/config-components
  components: true,

  // Modules for dev and build (recommended): https://go.nuxtjs.dev/config-modules
  buildModules: [
    '@nuxtjs/vuetify',
    ['@nuxtjs/router', {
        path: 'router',
        fileName: 'index.js',
        keepDefaultRouter: true,
    }]
  ],
  // Modules: https://go.nuxtjs.dev/config-modules
  modules: [
    [
      '@nuxtjs/firebase',
      {
        config: {
          apiKey: "AIzaSyD-7Ts6Yn6nTRJUwxPDVJ_5i0wyU11vwM0",
          authDomain: "rzk-market-ua.firebaseapp.com",
          projectId: "rzk-market-ua",
          storageBucket: "rzk-market-ua.appspot.com",
          messagingSenderId: "741872790396",
          appId: "1:741872790396:web:10ca22e384040f400c92f9",
          measurementId: "G-6KCV0R018E"
        },
        services: {
          auth: true, // Just as example. Can be any other service.
          firestore: true,
          analytics: true,
        }
      }
    ],
    '@nuxt/http',
    'nuxt-custom-headers'
  ],
  // moving the build directory into firebase functions folder for deployment
  //buildDir: '../functions/.nuxt',
  // Build Configuration: https://go.nuxtjs.dev/config-build
  build: {
  }
};
