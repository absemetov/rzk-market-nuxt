<template>
  <v-card
    max-width="375"
    class="mx-auto"
  >
    <v-card-title>
      Nadir Absemetov
    </v-card-title>
    <v-img src="//gravatar.com/avatar/a271283ed28c06443473f6d58acfa988?s=375"></v-img>

    <v-list>

      <v-list-item>
        <v-list-item-icon>
          <v-icon color="indigo">
            mdi-facebook
          </v-icon>
        </v-list-item-icon>
        <v-list-item-content>
          <v-list-item-title>
            <a href="//www.facebook.com/absemetov" target="_blank" title="facebook">Facebook</a>
          </v-list-item-title>
        </v-list-item-content>
      </v-list-item>

      <v-divider inset></v-divider>

      <v-list-item>
        <v-list-item-icon>
          <v-icon color="indigo">
            mdi-instagram
          </v-icon>
        </v-list-item-icon>
        <v-list-item-content>
          <v-list-item-title>
            <a href="//www.instagram.com/nadir.absemetov" target="_blank" title="instagram">Instagram</a>
          </v-list-item-title>
        </v-list-item-content>
      </v-list-item>

      <v-divider inset></v-divider>

      <v-list-item>
        <v-list-item-icon>
          <v-icon color="indigo">
            mdi-map
          </v-icon>
        </v-list-item-icon>
        <v-list-item-content>
          <v-list-item-title>
            <a href="//medium.com/@absemetov" target="_blank" title="medium">Medium</a>
          </v-list-item-title>
        </v-list-item-content>
      </v-list-item>

      <v-divider inset></v-divider>

      <v-list-item>
        <v-list-item-icon>
          <v-icon color="indigo">
            mdi-github
          </v-icon>
        </v-list-item-icon>
        <v-list-item-content>
          <v-list-item-title>
            <a href="//github.com/absemetov" target="_blank" title="github">Github</a>
          </v-list-item-title>
        </v-list-item-content>
      </v-list-item>

      <v-divider inset></v-divider>

      <v-list-item>
        <v-list-item-icon>
          <v-icon color="indigo">
            mdi-youtube
          </v-icon>
        </v-list-item-icon>
        <v-list-item-content>
          <v-list-item-title>
            <a href="//youtube.com/channel/UCM2yYZRK5GDp9XW352Q3n5Q" target="_blank" title="youtube">Youtube</a>
          </v-list-item-title>
        </v-list-item-content>
      </v-list-item>

      <v-divider inset></v-divider>

      <v-list-item>
        <v-list-item-icon>
          <v-icon color="indigo">
            mdi-email
          </v-icon>
        </v-list-item-icon>

        <v-list-item-content>
          <v-list-item-title>
            <a href="mailto:nadir@absemetov.org.ua?subject=absemetov.org.ua" target="_blank" title="e-mail">nadir@absemetov.org.ua</a>
          </v-list-item-title>
        </v-list-item-content>
      </v-list-item>
    </v-list>
  </v-card>
</template>

<script>
export default {
  head: {
    title: 'Nadir Absemetov',
    meta: [
      {
        hid: 'description',
        name: 'description',
        content: 'Nadir Absemetov, Сайт Надира Абсеметова.'
      },
      {
        hid: 'keywords',
        name: 'keywords',
        content: 'надир, абсеметов, nadir, absemetov, абсеметов надир, absemetov nadir'
      }
    ],
    link: [{ hid: 'icon', rel: 'icon', type: 'image/x-icon', href: '/favicons/absemetov.org.ua.ico' }]
  }
}
</script>
